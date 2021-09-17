#include "stdafx.h"
#include "MainScene.h"
#include "Stage1.h"
#include "Stage2.h"
#include "RankScene.h"
#include "InputScoreScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}
void MainScene::Init()
{
    ObjMgr->Release();
    GameInfo->Init();

    GameInfo->m_Score = 0;
    GameInfo->MaxScore = 0;

    Camera::GetInst()->m_Position = Vec2(0,0);

    m_Title = Sprite::Create(L"Painting/MainScreen/Title.png");
    m_Title->SetPosition(1920 / 2, 1080 / 2-300);
  
    m_MainScene = Sprite::Create(L"Painting/MainScreen/Main.png");
    m_MainScene->SetPosition(1920 / 2, 1080 / 2);
  
    m_Blind = Sprite::Create(L"Painting/MainScreen/blind.png");
    m_Blind->SetPosition(1920 / 2, 1080 / 2);

    m_Button[0] = Sprite::Create(L"Painting/MainScreen/Start.png");
    m_Button[0]->SetPosition(250, 940);

    m_Button[1] = Sprite::Create(L"Painting/MainScreen/Ranking.png");
    m_Button[1]->SetPosition(1920/2, 940);

    m_Button[2] = Sprite::Create(L"Painting/MainScreen/Help.png");
    m_Button[2]->SetPosition(1850, 930);
    m_Button[2]->SetScale(0.5f, 0.5f);

    m_Button[3] = Sprite::Create(L"Painting/MainScreen/Exit.png");
    m_Button[3]->SetPosition(1600, 940);

    std::cout << "MainScene �̵�" << std::endl;
    GameInfo->m_Scene = StageScene::NONE;
    ShackX = 0;
    acc1 = 0;
    acc2 = 0;
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{
    ShackX += dt;
    if (ShackX > 2) {
        acc1+= dt;
        m_Title->Translate(0, 100* acc1 * dt);
    }
    else {
        acc2 += dt;
        m_Title->Translate(0, -100* acc2 * dt);
    }
    if (ShackX > 1) {
        acc2 -= 2*dt;
    }
    if (ShackX > 3) {
        acc1 -= 2 * dt;
    }
    if (ShackX > 4) {
        ShackX = 0;
        acc1 = 0;
        acc2 = 0;
    }
    if (INPUT->GetKey('Q') == KeyState::DOWN) {
        SoundMgr::GetInst()->Open(L"../Sound/Test.wav");
    }
    if (INPUT->GetKey('W') == KeyState::DOWN) {
        SoundMgr::GetInst()->Play();
    }
    if (INPUT->GetKey('E') == KeyState::DOWN) {
        SoundMgr::GetInst()->Stop();
    } 
    if (INPUT->GetKey('R') == KeyState::DOWN) {
        SoundMgr::GetInst()->Pause();
    }
    //���ӽ���, ���ӼҰ�, ���ӹ��, ���ӷ�ŷ(score), ũ����(credit)
    if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[0]) && INPUT->GetButtonDown())
    {
        SceneDirector::GetInst()->ChangeScene(new Stage1());
        INPUT->ButtonDown(false);
    }
    else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[1]) && INPUT->GetButtonDown())
    {
        SceneDirector::GetInst()->ChangeScene(new InputScoreScene());
        INPUT->ButtonDown(false);
    }
    else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[2]) && INPUT->GetButtonDown())
    {
        SceneDirector::GetInst()->ChangeScene(new RankScene());
        INPUT->ButtonDown(false);
    }
    else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[3]) && INPUT->GetButtonDown())
    {
        App::GetInst()->Release();
        exit(0);
    }
 
    GameInfo->CheatKey();
}

void MainScene::Render()
{
    m_MainScene->Render();
    m_Blind->Render();
    m_Button[0]->Render();
    m_Button[1]->Render();
    m_Button[2]->Render();
    m_Button[3]->Render();
    m_Title->Render();
}

