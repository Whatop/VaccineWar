#include "stdafx.h"
#include "SoundMgr.h"


SoundMgr::SoundMgr()
{
}


SoundMgr::~SoundMgr()
{
}

HRESULT SoundMgr::Open(LPCWSTR szFileName)
{
    HRESULT hr;

    //if (this->pGraphBuilder)
     //   this->Close();

    hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&(this->pGraphBuilder));
    if (FAILED(hr))
    {
        std::cout << "생성 불가" << std::endl;
        return hr;
    }

    hr = this->pGraphBuilder->RenderFile(szFileName, NULL);
    if (FAILED(hr))
    {
        std::cout << "생성 불가" << std::endl;
        return hr;
    }

    hr = this->pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
    if (FAILED(hr))
    {
        std::cout << "인터페이스 못가져옴."<< std::endl;
        return hr;
    }

    hr = this->pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&pMediaSeeking);
    if (FAILED(hr))
    {
        std::cout << "인터페이스 못가져옴." << std::endl;
        return hr;
    }
    std::cout << "파일로 필터 그래프가 생성되었습니다." << szFileName << std::endl;
    return S_OK;
}

HRESULT SoundMgr::Play()
{
    HRESULT hr;

    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] IMediaControl 인터페이스가 없어 Play를 할 수 없습니다. HRESULT: 0x%x\n" << std::endl;
        return E_POINTER;
    }



    hr = pMediaControl->Run();
    
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] IMediaControl의 Run()이 실행되지 않습니다. HRESULT: 0x%x\n" << std::endl;
        return hr;
    }



    std::cout << "[DomonePlayer] 재생이 시작됩니다." << std::endl;
    return S_OK;
}

HRESULT SoundMgr::Stop()
{
    HRESULT hr;



    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] IMediaControl 인터페이스가 없어 Stop를 할 수 없습니다. HRESULT: 0x%x\n" << std::endl;
        return E_POINTER;
    }



    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] pMediaSeeking 인터페이스가 없어 Stop를 할 수 없습니다. HRESULT: 0x%x\n" << std::endl;
        return E_POINTER;
    }



    hr = pMediaControl->Stop();
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] IMediaControl의 Stop()이 실행되지 않습니다. HRESULT: 0x%x\n" << std::endl;
        return hr;
    }



    LONGLONG nStartPosition = 0;
    hr = pMediaSeeking->SetPositions(&nStartPosition, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] 재생 위치를 변경할 수 없습니다." << std::endl;

        return hr;
    }



    std::cout << "[DomonePlayer] 재생이 중지됩니다." << std::endl;
    return S_OK;
}

HRESULT SoundMgr::Pause()
{   
    HRESULT hr;

    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] IMediaControl 인터페이스가 없어 Pause를 할 수 없습니다. HRESULT: 0x%x\n" << std::endl;

        return E_POINTER;
    }

    hr = pMediaControl->Pause();
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] IMediaControl의 Pause()가 실행되지 않습니다. HRESULT: 0x%x\n" << std::endl;
        return hr;
    }



    std::cout << "[DomonePlayer] 일시정지 되었습니다." << std::endl;
    return S_OK;
}

void SoundMgr::SetOwner(HWND hOwner)
{
    this->hOwner = hOwner;
}

/*
void SoundMgr::Play(const WCHAR* pFileName, bool loop)
{
	WCHAR szFullPath[256] = L"../Sound/";
	lstrcatW(szFullPath, pFileName);

	if (!loop)
	{
		PlaySound(szFullPath, NULL, SND_ASYNC | SND_NOSTOP | SND_FILENAME);
	}
	else if (loop)
	{
		PlaySound(szFullPath, NULL, SND_ASYNC | SND_LOOP | SND_NOSTOP | SND_FILENAME);
	}
}

void SoundMgr::Stop()
{
	PlaySound(nullptr, NULL, SND_ASYNC);
}

DWORD SoundMgr::LoadWAV(HWND hWnd, LPCTSTR lpszWave) {
	DWORD Result;
	//DWORD wDeviceID;
	mciOpen.lpstrDeviceType = L"WaveAudio";
	mciOpen.lpstrElementName = lpszWave;
	Result = mciSendCommand(mciOpen.wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

	//wDeviceID =	mciOpen.wDeviceID;
	if (Result)
		return Result;

	mciPlay.dwCallback = (DWORD)hWnd;

	if (Result)
		return Result;

	return 0;
}*/