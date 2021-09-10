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

    m_MainScene = Sprite::Create(L"Painting/MainScreen/Main.png");
    m_MainScene->SetPosition(1920 / 2, 1080 / 2);

    m_Button[0] = Sprite::Create(L"Painting/Button/start.png");
    m_Button[0]->SetPosition(300, 100);

    m_Button[1] = Sprite::Create(L"Painting/Button/way.png");
    m_Button[1]->SetPosition(300, 300);

    m_Button[2] = Sprite::Create(L"Painting/Button/rank.png");
    m_Button[2]->SetPosition(300, 500);

    m_Button[3] = Sprite::Create(L"Painting/Button/exit.png");
    m_Button[3]->SetPosition(300, 700);

    std::cout << "MainScene 이동" << std::endl;
    GameInfo->m_Scene = StageScene::NONE;
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float time)
{
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
    //게임시작, 게임소개, 게임방법, 게임랭킹(score), 크래딧(credit)
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
    m_Button[0]->Render();
    m_Button[1]->Render();
    m_Button[2]->Render();
    m_Button[3]->Render();
}

