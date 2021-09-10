#pragma once


#ifndef DOMONEPLAYER_H
#define DOMONEPLAYER_H
class SoundMgr :public Singleton<SoundMgr>
{
	//MCI_OPEN_PARMS mciOpen; // 파일을 로드
	//MCI_PLAY_PARMS mciPlay; // 파일을 재생
	//MCI_STATUS_PARMS mciStatus; // 파일의 상태
	IGraphBuilder* pGraphBuilder;        // 필터 그래프 매니저 역할을 하는 인터페이스
	IMediaControl* pMediaControl;       // 재생/일시정지/정지 등을 수행하기 위한 인터페이스
	IMediaSeeking* pMediaSeeking;    // 재생 위치를 읽어오거나 변경하기 위한 인터페이스

public:
	DWORD Sound1, Sound2;

	SoundMgr();
	~SoundMgr();

	//void Play(const WCHAR* pFileName, bool loop);
	//void Stop();

	//DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);


	HRESULT Open(LPCWSTR szFileName);// 주어진 파일로 필터 그래프를 구성한다.
	HRESULT Play(); // 미디어 파일을 재생한다.
	HRESULT Stop();        // 재생을 중단한다.
	HRESULT Pause();     // 재생을 일시정지한다.

	void SetOwner(HWND hOwner);

	HWND hOwner;
};
#endif

