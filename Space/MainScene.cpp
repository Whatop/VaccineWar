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

    BGInit();

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
    m_Button[2]->SetPosition(1850, 75);
    m_Button[2]->SetScale(0.5f, 0.5f);

    m_Button[3] = Sprite::Create(L"Painting/MainScreen/Exit.png");
    m_Button[3]->SetPosition(1600, 940);

    std::cout << "MainScene 이동" << std::endl;
    GameInfo->m_Scene = StageScene::MAINSCENE;
    ShackX = 0;
    acc1 = 0;
    acc2 = 0;
    isMovePlayer = false;

    PlayerAnimation = new Animation();
    PlayerAnimation->Init(0.2f, true);
    PlayerAnimation->AddContinueFrame(L"Painting/Player/", 0, 3);
    PlayerAnimation->SetPosition(100, 700);
    PlayerAnimation->SetScale(0.55f, 0.55f);

    Player = Sprite::Create(L"Painting/Player/Player0.png");
    Player->SetPosition(100,700);
    Player->SetScale(0.55f, 0.55f);
    AccTime = 1.f;
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float Time)
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
   
 
    GameInfo->CheatKey();
    if (GameInfo->m_Scene == StageScene::MAINSCENE) {
        if (!GameInfo->isPause) {
            MoveBG();
            ResetBG();
        }
        PlayerAnimation->Update(deltaTime, Time);
        if (isMovePlayer) {
            AccTime += dt;
            PlayerAnimation->m_Position.x += 150 * AccTime * dt;
            Player->m_Position.x += 150 * AccTime * dt;
           
            if (m_Title->A > 0)
                m_Title->A -= 1;
            else 
                m_Title->A = 0;

            for (int i = 0; i < 4; i++) {
                if (m_Button[i]->A > 0)
                    m_Button[i]->A -= 1;
                else
                    m_Button[i]->A = 0;
            }
            if (AccTime > 5) {
                for (int i = 0; i < 6; i++) {
                    if (m_BackGround[i][0]->A > 0)
                        m_BackGround[i][0]->A -=1;
                    else
                        m_BackGround[i][0]->A = 0;

                    if (m_BackGround[i][1]->A > 0)
                        m_BackGround[i][1]->A -=1;
                    else
                        m_BackGround[i][1]->A -= 0;
                }
              
            }
            if (AccTime > 8) {
                SceneDirector::GetInst()->ChangeScene(new Stage1());
            }
        }
        else {
            //게임시작, 게임소개, 게임방법, 게임랭킹(score), 크래딧(credit)
            if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[0]) && INPUT->GetButtonDown())
            {
                isMovePlayer = true;
                INPUT->ButtonDown(false);
            }
            else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[1]) && INPUT->GetButtonDown())
            {
                SceneDirector::GetInst()->ChangeScene(new RankScene());
                INPUT->ButtonDown(false);
            }
            else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[2]) && INPUT->GetButtonDown())
            {
                SceneDirector::GetInst()->ChangeScene(new InputScoreScene());
                INPUT->ButtonDown(false);
            }
            else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[3]) && INPUT->GetButtonDown())
            {
                App::GetInst()->Release();
                exit(0);
            }
        }
    }
}

void MainScene::Render()
{
    for (int i = 0; i < 6; i++) {
        m_BackGround[i][0]->Render();
        m_BackGround[i][1]->Render();
    }
    m_Button[0]->Render();
    m_Button[1]->Render();
    m_Button[2]->Render();
    m_Button[3]->Render();
    m_Title->Render();
    Player->Render();
    PlayerAnimation->Render();
   
}

void MainScene::BGInit()
{
    for (int i = 0; i < 6; i++) {
        m_BackGround[i][0] = Sprite::Create(L"Painting/GameScreen/Stage1/" + std::to_wstring(i) + L".png");
        m_BackGround[i][0]->SetPosition(1920 / 2, 1080 / 2);
        m_BackGround[i][1] = Sprite::Create(L"Painting/GameScreen/Stage1/" + std::to_wstring(i) + L".png");
        m_BackGround[i][1]->SetPosition(m_BackGround[i][0]->m_Position.x + 1920, 1080 / 2);
        m_BackGround[i][0]->SetScale(1, 1);
        m_BackGround[i][1]->SetScale(1, 1);
    }
}

void MainScene::MoveBG()
{
    for (int i = 0; i < 2; i++) {
        m_BackGround[5][i]->m_Position.x -= 10 * dt;
        m_BackGround[4][i]->m_Position.x -= 15 * dt;
        m_BackGround[3][i]->m_Position.x -= 25 * dt;
        m_BackGround[2][i]->m_Position.x -= 50 * dt;
        m_BackGround[1][i]->m_Position.x -= 75 * dt;
        m_BackGround[0][i]->m_Position.x -= 100 * dt;
    }
}

void MainScene::ResetBG()
{
    for (int i = 0; i < 5; i++) {
        if (m_BackGround[i][0]->m_Position.x <= -1920 / 2) {
            m_BackGround[i][0]->m_Position.x = m_BackGround[i][0]->m_Position.x + m_BackGround[0][0]->m_Size.x * 2;
        }
        if (m_BackGround[i][1]->m_Position.x <= -1920 / 2) {
            m_BackGround[i][1]->m_Position.x = m_BackGround[i][1]->m_Position.x + m_BackGround[0][1]->m_Size.x * 2;
        }
    }
}