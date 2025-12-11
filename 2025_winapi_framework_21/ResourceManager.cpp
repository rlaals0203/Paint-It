#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"

bool ResourceManager::Init()
{
	//fs::path curPath  = fs::current_path();
	//// todo: release build path
	//m_resourcePath = curPath.parent_path() / L"Output\\build\\Resource\\";

	wchar_t buf[MAX_PATH] = {}; // windows 최대 경로 길이
	::GetModuleFileNameW(nullptr, buf, MAX_PATH); // 현재 실행중인 exe 경로 buf에 저장   
	fs::path exeDir = fs::path(buf).parent_path();                //  buf 전체 경로를 path 객체로 가서 디렉토리만 추출
	fs::path resourceDir = exeDir.parent_path() / L"build" / L"Resource\\"; // release모드일때 build 한번더 붙이는거 무시
	m_resourcePath = resourceDir.native();
	if (!RegisterFontFile(L"Font\\NeoDunggeunmoPro-Regular.ttf"))
		return false;
	RegisterGDI();
	RegisterTexture();

	FMOD::System_Create(&m_pSoundSystem); // 시스템 생성
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init(64, FMOD_INIT_NORMAL, nullptr);
	RegisterSound();
	return true;
}

void ResourceManager::FmodUpdate()
{
	if (m_pSoundSystem)
		m_pSoundSystem->update();
}

void ResourceManager::Release()
{
	std::unordered_map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTexture.begin(); iter != m_mapTexture.end(); ++iter)
		SAFE_DELETE(iter->second);
	m_mapTexture.clear();
	ReleaseGDI();
	ReleaseFonts();

	std::unordered_map<wstring, SoundInfo*>::iterator iterSound;
	for (iterSound = m_mapSounds.begin(); iterSound != m_mapSounds.end(); ++iterSound)
		SAFE_DELETE(iterSound->second);
	m_mapSounds.clear();

	m_pSoundSystem->close();
	m_pSoundSystem->release();
}

void ResourceManager::RegisterGDI()
{
	// BRUSH
	m_Brushs[(UINT)BrushType::HOLLOW] = (HBRUSH)::GetStockObject(HOLLOW_BRUSH);
	m_Brushs[(UINT)BrushType::LIGHTRED] = (HBRUSH)::CreateSolidBrush(RGB(255, 150, 150));
	m_Brushs[(UINT)BrushType::GREEN] = (HBRUSH)::CreateSolidBrush(RGB(134, 229, 134));
	m_Brushs[(UINT)BrushType::LAZER] = (HBRUSH)::CreateSolidBrush(RGB(108, 141, 250));
	m_Brushs[(UINT)BrushType::LAZER2] = (HBRUSH)::CreateSolidBrush(RGB(200, 250, 250));
	m_Brushs[(UINT)BrushType::BLACK] = (HBRUSH)::CreateSolidBrush(RGB(0, 0, 0));
	m_Brushs[(UINT)BrushType::RED] = (HBRUSH)::CreateSolidBrush(RGB(200, 30, 30));
	m_Brushs[(UINT)BrushType::YELLOW] = (HBRUSH)::CreateSolidBrush(RGB(200, 150, 30));
	m_Brushs[(UINT)BrushType::BLUE] = (HBRUSH)::CreateSolidBrush(RGB(30, 30, 200));
	m_Brushs[(UINT)BrushType::WHITE] = (HBRUSH)::CreateSolidBrush(RGB(255, 255, 255));
	m_Brushs[(UINT)BrushType::STRINGLASER] = (HBRUSH)::CreateSolidBrush(RGB(200, 100, 25));

	// PEN 
	m_Pens[(UINT)PenType::GREEN] = ::CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pens[(UINT)PenType::DANGER1] = ::CreatePen(PS_SOLID, 2, RGB(255, 50, 50));
	m_Pens[(UINT)PenType::DANGER2] = ::CreatePen(PS_SOLID, 2, RGB(255, 125, 50));
	m_Pens[(UINT)PenType::LIGHTRED] = ::CreatePen(PS_SOLID, 1, RGB(255, 150, 150));
	m_Pens[(UINT)PenType::LAZER] = ::CreatePen(PS_SOLID, 5, RGB(140, 176, 255));
	m_Pens[(UINT)PenType::LAZER2] = ::CreatePen(PS_SOLID, 5, RGB(150, 200, 250));
	m_Pens[(UINT)PenType::BLACK] = ::CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
	m_Pens[(UINT)PenType::RED] = ::CreatePen(PS_SOLID, 5, RGB(200, 30, 30));
	m_Pens[(UINT)PenType::YELLOW] = ::CreatePen(PS_SOLID, 5, RGB(200, 150, 30));
	m_Pens[(UINT)PenType::BLUE] = ::CreatePen(PS_SOLID, 5, RGB(30, 30, 200));
	m_Pens[(UINT)PenType::WHITE] = ::CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
	m_Pens[(UINT)PenType::STRINGLASER] = ::CreatePen(PS_SOLID, 5, RGB(200, 125, 30));

	// 폰트 등록
	RegisterFont(FontType::TITLE, L"NeoDunggeunmoPro-Regular", 0);
	RegisterFont(FontType::UI, L"NeoDunggeunmoPro-Regular", 0);
}

void ResourceManager::ReleaseGDI()
{
	for (int i = 0; i < (UINT)PenType::END; ++i)
		::DeleteObject(m_Pens[i]);
	for (int i = 1; i < (UINT)BrushType::END; ++i)
		// Hollow 제외하고
		::DeleteObject(m_Brushs[i]);
	for (int i = 0; i < (UINT)FontType::END; ++i)
		::DeleteObject(m_Fonts[i]);
}


bool ResourceManager::RegisterFontFile(const wstring& _path)
{
	wstring fontPath = m_resourcePath;
	fontPath += _path;
	if (!(AddFontResourceExW(fontPath.c_str(), FR_PRIVATE, 0) > 0))
		return false;
	m_vecFontFiles.push_back(fontPath);
	return true;
}

void ResourceManager::ReleaseFonts()
{
	for (const auto& path : m_vecFontFiles)
		::RemoveFontResourceExW(path.c_str(), FR_PRIVATE, 0);
	m_vecFontFiles.clear();
}

void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (FindSound(_key) || !m_pSoundSystem)
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// 루프할지 말지 결정
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // 반복 출력
	if (!_isLoop)
		eMode = FMOD_DEFAULT; // 사운드 1번만 출력
	FMOD::Sound* p = nullptr;

	// BGM면 stream, 아니면 sound
	// 팩토리함수
	//// 사운드 객체를 만드는 것은 system임.
	//						//파일경로,  FMOD_MODE, NULL, &sound
	FMOD_RESULT r = _isLoop
		? m_pSoundSystem->createStream(str.c_str(), eMode, nullptr, &p)
		: m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &p);

	if (r != FMOD_OK || !p)
		return;

	SoundInfo* pSound = new SoundInfo;
	pSound->IsLoop = _isLoop;
	pSound->pSound = p;
	m_mapSounds.insert({ _key, pSound });

}

void ResourceManager::Play(const wstring& _key)
{
	SoundInfo* pSound = FindSound(_key);
	if (!pSound)
		return;

	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!pSound->IsLoop)
		eChannel = SOUND_CHANNEL::EFFECT;

	FMOD::Channel* pNewChannel = nullptr;
	m_pSoundSystem->playSound(pSound->pSound, nullptr, false, &pNewChannel);

	// 재생 직후 바로 볼륨 적용!
	if (pNewChannel)
	{
		pNewChannel->setVolume(m_Volume[(UINT)eChannel]);  // 저장된 볼륨 값 적용
	}

	m_pChannel[(UINT)eChannel] = pNewChannel;
}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
{
	// 볼륨 값 저장
	m_Volume[(UINT)_channel] = _vol;

	// 현재 재생 중인 채널에도 적용
	if (m_pChannel[(UINT)_channel])
	{
		bool isPlaying = false;
		m_pChannel[(UINT)_channel]->isPlaying(&isPlaying);

		if (isPlaying)
		{
			m_pChannel[(UINT)_channel]->setVolume(_vol);
		}
	}
}

void ResourceManager::Stop(SOUND_CHANNEL _channel)
{
	m_pChannel[(UINT)_channel]->stop();

}


void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}
SoundInfo* ResourceManager::FindSound(const wstring& _key)
{
	std::unordered_map<wstring, SoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}

void ResourceManager::RegisterSound()
{
	LoadSound(L"laser", L"Sound\\laser.mp3", false);
	LoadSound(L"smash", L"Sound\\smash.mp3", false);
	LoadSound(L"click", L"Sound\\Click.mp3", false);
	LoadSound(L"hover", L"Sound\\Hover.mp3", false);
	LoadSound(L"blackhole", L"Sound\\blackhole.wav", false);
	LoadSound(L"hit", L"Sound\\hit.mp3", false);
	LoadSound(L"shield", L"Sound\\shield.wav", false);
	LoadSound(L"exlosion", L"Sound\\exlosion.wav", false);
	LoadSound(L"prismbreak", L"Sound\\prismbreak.wav", false);
	LoadSound(L"boss1", L"Sound\\boss01.wav", true);
	LoadSound(L"boss2", L"Sound\\boss02.wav", true);
	LoadSound(L"boss3", L"Sound\\boss03.wav", true);
}

void ResourceManager::RegisterFont(FontType _type, const wstring& _name, int _height, int _weight, bool _italic, int _quality)
{

	HFONT h = ::CreateFont(_height, 0, 0, 0, _weight, _italic, false, false, HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, _quality, DEFAULT_PITCH || FF_DONTCARE, _name.c_str());
	m_Fonts[(UINT)_type] = h;
}



void ResourceManager::RegisterTexture()
{
	LoadTexture(L"bullet", L"Texture\\Bullet.bmp");
	LoadTexture(L"player", L"Texture\\PlayerSheet.bmp");
	LoadTexture(L"rplayer", L"Texture\\RPlayerSheet.bmp");
	LoadTexture(L"fireboss", L"Texture\\FireBoss.bmp");
	LoadTexture(L"firebossblink", L"Texture\\FireBossBlink.bmp");
	LoadTexture(L"playerblink", L"Texture\\PlayerBlink.bmp");
	LoadTexture(L"rplayerblink", L"Texture\\RPlayerBlink.bmp");
	LoadTexture(L"brush", L"Texture\\Brush.bmp");
	LoadTexture(L"background1", L"Texture\\background1.bmp");
	LoadTexture(L"smashsmoke", L"Texture\\BossSmashSmoke.bmp");
	LoadTexture(L"floor1", L"Texture\\floor1.bmp");
	LoadTexture(L"floor2", L"Texture\\floor2.bmp");
	LoadTexture(L"floor3", L"Texture\\floor3.bmp");
	LoadTexture(L"knife", L"Texture\\knife.bmp");
	LoadTexture(L"fireexplosion", L"Texture\\fireexplosion.bmp");
	LoadTexture(L"firebullet", L"Texture\\firebossbullet.bmp");
	LoadTexture(L"prismboss", L"Texture\\PrismBoss.bmp");
	LoadTexture(L"bluebackground", L"Texture\\bluebackground.bmp");
	LoadTexture(L"bossshield", L"Texture\\bossshield.bmp");
	LoadTexture(L"torch", L"Texture\\torch.bmp");
	LoadTexture(L"background3", L"Texture\\background3.bmp");
	LoadTexture(L"oil1", L"Texture\\oil1.bmp");
	LoadTexture(L"oil2", L"Texture\\oil2.bmp");
	LoadTexture(L"oil3", L"Texture\\oil3.bmp");
	LoadTexture(L"skull", L"Texture\\skull.bmp");
	LoadTexture(L"playerbullet", L"Texture\\playerbullet.bmp");
	LoadTexture(L"button", L"Texture\\UIButton.bmp");
	LoadTexture(L"buttonhover", L"Texture\\UIButton_HoverRed.bmp");
	LoadTexture(L"panel", L"Texture\\UIPanel.bmp");
	LoadTexture(L"slider", L"Texture\\UISliderEmpty.bmp");
	LoadTexture(L"slidericon", L"Texture\\UISliderIcon.bmp");
	LoadTexture(L"sliderfill", L"Texture\\UISliderFull.bmp");
	LoadTexture(L"xbutton", L"Texture\\UIXButton.bmp");
	LoadTexture(L"crosshair", L"Texture\\crosshair.bmp");
	LoadTexture(L"platform", L"Texture\\platform.bmp");
	LoadTexture(L"blackhole", L"Texture\\blackhole.bmp");
	LoadTexture(L"dangermark1", L"Texture\\dangermark1.bmp");
	LoadTexture(L"dangermark2", L"Texture\\dangermark2.bmp");
	LoadTexture(L"artboss", L"Texture\\artboss.bmp");
	LoadTexture(L"originpoint", L"Texture\\Boss03_OriginPointSheet.bmp");
	LoadTexture(L"explosion", L"Texture\\Boss03_ExplosionSheet.bmp");
	LoadTexture(L"bomb", L"Texture\\Boss03_Bomb.bmp");
	LoadTexture(L"bombblink", L"Texture\\Boss03_BombBlink.bmp");
	LoadTexture(L"yellowprojectile", L"Texture\\yellowprojectile.bmp");
	LoadTexture(L"artbossblink", L"Texture\\artbossblink.bmp");
	LoadTexture(L"pond", L"Texture\\Pond.bmp");
	LoadTexture(L"healpack", L"Texture\\healpack.bmp");
	LoadTexture(L"prismbossblink2", L"Texture\\prismbossblink2.bmp");
	LoadTexture(L"prismbossblink", L"Texture\\prismbossblink.bmp");
	LoadTexture(L"playerredbullet", L"Texture\\playerredbullet.bmp");
	LoadTexture(L"prismcrystal", L"Texture\\prismcrystal.bmp");
	LoadTexture(L"title", L"Texture\\title.bmp");
}


void ResourceManager::LoadTexture(const wstring& _key, const wstring& _path)
{
	Texture* pTex = GetTexture(_key);
	// 못찾았으면 리턴
	if (nullptr != pTex)
		return;
	// 처음에 없을거니 경로 찾아서
	wstring texPath = m_resourcePath;
	texPath += _path;

	// 만들어서
	pTex = new Texture;
	pTex->Load(texPath); // 텍스처 자체 로드
	pTex->SetKey(_key); // 키 경로 세팅
	pTex->SetRelativePath(texPath);
	m_mapTexture.insert({ _key,pTex }); // 맵에 저장
}

Texture* ResourceManager::GetTexture(const wstring& _key)
{
	auto iter = m_mapTexture.find(_key);
	if (iter != m_mapTexture.end())
		return iter->second;
	return nullptr;
}