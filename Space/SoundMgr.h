#pragma once


#ifndef DOMONEPLAYER_H
#define DOMONEPLAYER_H
class SoundMgr :public Singleton<SoundMgr>
{
	//MCI_OPEN_PARMS mciOpen; // ������ �ε�
	//MCI_PLAY_PARMS mciPlay; // ������ ���
	//MCI_STATUS_PARMS mciStatus; // ������ ����
	IGraphBuilder* pGraphBuilder;        // ���� �׷��� �Ŵ��� ������ �ϴ� �������̽�
	IMediaControl* pMediaControl;       // ���/�Ͻ�����/���� ���� �����ϱ� ���� �������̽�
	IMediaSeeking* pMediaSeeking;    // ��� ��ġ�� �о���ų� �����ϱ� ���� �������̽�

public:
	DWORD Sound1, Sound2;

	SoundMgr();
	~SoundMgr();

	//void Play(const WCHAR* pFileName, bool loop);
	//void Stop();

	//DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave);


	HRESULT Open(LPCWSTR szFileName);// �־��� ���Ϸ� ���� �׷����� �����Ѵ�.
	HRESULT Play(); // �̵�� ������ ����Ѵ�.
	HRESULT Stop();        // ����� �ߴ��Ѵ�.
	HRESULT Pause();     // ����� �Ͻ������Ѵ�.

	void SetOwner(HWND hOwner);

	HWND hOwner;
};
#endif

