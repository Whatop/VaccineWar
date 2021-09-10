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
        std::cout << "���� �Ұ�" << std::endl;
        return hr;
    }

    hr = this->pGraphBuilder->RenderFile(szFileName, NULL);
    if (FAILED(hr))
    {
        std::cout << "���� �Ұ�" << std::endl;
        return hr;
    }

    hr = this->pGraphBuilder->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);
    if (FAILED(hr))
    {
        std::cout << "�������̽� ��������."<< std::endl;
        return hr;
    }

    hr = this->pGraphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&pMediaSeeking);
    if (FAILED(hr))
    {
        std::cout << "�������̽� ��������." << std::endl;
        return hr;
    }
    std::cout << "���Ϸ� ���� �׷����� �����Ǿ����ϴ�." << szFileName << std::endl;
    return S_OK;
}

HRESULT SoundMgr::Play()
{
    HRESULT hr;

    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] IMediaControl �������̽��� ���� Play�� �� �� �����ϴ�. HRESULT: 0x%x\n" << std::endl;
        return E_POINTER;
    }



    hr = pMediaControl->Run();
    
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] IMediaControl�� Run()�� ������� �ʽ��ϴ�. HRESULT: 0x%x\n" << std::endl;
        return hr;
    }



    std::cout << "[DomonePlayer] ����� ���۵˴ϴ�." << std::endl;
    return S_OK;
}

HRESULT SoundMgr::Stop()
{
    HRESULT hr;



    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] IMediaControl �������̽��� ���� Stop�� �� �� �����ϴ�. HRESULT: 0x%x\n" << std::endl;
        return E_POINTER;
    }



    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] pMediaSeeking �������̽��� ���� Stop�� �� �� �����ϴ�. HRESULT: 0x%x\n" << std::endl;
        return E_POINTER;
    }



    hr = pMediaControl->Stop();
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] IMediaControl�� Stop()�� ������� �ʽ��ϴ�. HRESULT: 0x%x\n" << std::endl;
        return hr;
    }



    LONGLONG nStartPosition = 0;
    hr = pMediaSeeking->SetPositions(&nStartPosition, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] ��� ��ġ�� ������ �� �����ϴ�." << std::endl;

        return hr;
    }



    std::cout << "[DomonePlayer] ����� �����˴ϴ�." << std::endl;
    return S_OK;
}

HRESULT SoundMgr::Pause()
{   
    HRESULT hr;

    if (!pMediaControl)
    {
        std::cout << "[DomonePlayer] IMediaControl �������̽��� ���� Pause�� �� �� �����ϴ�. HRESULT: 0x%x\n" << std::endl;

        return E_POINTER;
    }

    hr = pMediaControl->Pause();
    if (FAILED(hr))
    {
        std::cout << "[DomonePlayer] IMediaControl�� Pause()�� ������� �ʽ��ϴ�. HRESULT: 0x%x\n" << std::endl;
        return hr;
    }



    std::cout << "[DomonePlayer] �Ͻ����� �Ǿ����ϴ�." << std::endl;
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