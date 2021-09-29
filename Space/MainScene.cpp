#include "stdafx.h"
#include "MainScene.h"
#include "Stage1.h"
#include "Stage2.h"

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

    Camera::GetInst()->m_Position = Vec2(0, 0);

    m_Title = Sprite::Create(L"Painting/MainScreen/Title.png");
    m_Title->SetPosition(1920 / 2, 1080 / 2 - 300);

    m_Button[0] = Sprite::Create(L"Painting/MainScreen/Start.png");
    m_Button[0]->SetPosition(250, 940);

    m_Button[1] = Sprite::Create(L"Painting/MainScreen/Ranking.png");
    m_Button[1]->SetPosition(1920 / 2, 940);

    m_Button[2] = Sprite::Create(L"Painting/MainScreen/Help.png");
    m_Button[2]->SetPosition(1850, 75);
    m_Button[2]->SetScale(0.5f, 0.5f);

    m_Button[3] = Sprite::Create(L"Painting/MainScreen/Exit.png");
    m_Button[3]->SetPosition(1600, 940);

    std::cout << "MainScene 이동" << std::endl;
    GameInfo->m_Scene = StageScene::MAINSCENE;
    TM_Time = 0;
    TM_Down = 0;
    TM_Up = 0;
    isMovePlayer = false;

    PlayerAnimation = new Animation();
    PlayerAnimation->Init(0.2f, true);
    PlayerAnimation->AddContinueFrame(L"Painting/Player/", 0, 3);
    PlayerAnimation->SetPosition(100, 700);
    PlayerAnimation->SetScale(0.55f, 0.55f);

    Player = Sprite::Create(L"Painting/Player/Player0.png");
    Player->SetPosition(100, 700);
    Player->SetScale(0.55f, 0.55f);
    AccTime = 1.f;

    m_RankText = new TextMgr();
    m_RankText->Init(72, true, false, "DungGeunMo");

    RankScene = Sprite::Create(L"Painting/GameScreen/RankScene.png");
    RankScene->SetPosition(1920 / 2, 1080 / 2);
    RankScene->m_Visible = false;

    HelpScene = Sprite::Create(L"Painting/GameScreen/HelpScene.png");
    HelpScene->SetPosition(1920 / 2, 1080 / 2);
    HelpScene->m_Visible = false;

    isRankScene = false;
    isHelpScene = false;
}

void MainScene::Release()
{
}

void MainScene::Update(float deltaTime, float Time)
{
    TM_Time += dt;
    if (TM_Time > 2) {
        TM_Down += dt;
        m_Title->Translate(0, 100 * TM_Down * dt);
    }
    else {
        TM_Up += dt;
        m_Title->Translate(0, -100 * TM_Up * dt);
    }
    if (TM_Time > 1) {
        TM_Up -= 2 * dt;
    }
    if (TM_Time > 3) {
        TM_Down -= 2 * dt;
    }
    if (TM_Time > 4) {
        TM_Time = 0;
        TM_Down = 0;
        TM_Up = 0;
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

            if (m_Title->A - int(200 * dt) > 0)
                m_Title->A -= int(200 * dt);
            else
                m_Title->A = 0;

            for (int i = 0; i < 4; i++) {
                if (m_Button[i]->A - int(200 * dt) >   0)
                    m_Button[i]->A -= int(200 * dt);
                else
                    m_Button[i]->A = 0;
            }
            if (AccTime > 5) {
                for (int i = 0; i < 6; i++) {
                    if (m_BackGround[i][0]->A - int(200 * dt) > 0)
                        m_BackGround[i][0]->A -= int(200 * dt);
                    else
                        m_BackGround[i][0]->A = 0;

                    if (m_BackGround[i][1]->A - int(200 * dt) > 0)
                        m_BackGround[i][1]->A -= int(200 * dt);
                    else
                        m_BackGround[i][1]->A = 0;
                }

            }
            if (AccTime > 8) {
                SceneDirector::GetInst()->ChangeScene(new Stage1());
            }

        }
        else {
            if (isRankScene) {

                if (CollisionMgr::GetInst()->MouseWithBoxSize(RankScene) && (INPUT->GetButtonDown() || INPUT->GetKey(VK_SPACE) == KeyState::DOWN))
                {
                    RankScene->m_Visible = false;
                    isRankScene = false;

                    INPUT->ButtonDown(false);
                }
                for (int i = 0; i < 4; i++) {
                    if (m_Button[i]->A - int(200 * dt) > 0)
                        m_Button[i]->A -= int(200 * dt);
                    else
                        m_Button[i]->A = 0;
                }
                if (m_Title->A - int(200 * dt) > 0)
                    m_Title->A -= int(200 * dt);
                else
                    m_Title->A = 0;
            }
            else if (!isHelpScene && !isRankScene) {
                for (int i = 0; i < 4; i++) {
                    if (m_Button[i]->A + int(200 * dt) < 255)
                        m_Button[i]->A += int(200 * dt);
                    else
                        m_Button[i]->A = 255;
                }
                if (m_Title->A + int(200 * dt) < 255)
                    m_Title->A += int(200 * dt);
                else
                    m_Title->A = 255;
            }
            if (isHelpScene) {
                HelpScene->m_Visible = true;
                if (CollisionMgr::GetInst()->MouseWithBoxSize(HelpScene) && (INPUT->GetButtonDown() || INPUT->GetKey(VK_SPACE) == KeyState::DOWN))
                {
                    HelpScene->m_Visible = false;
                    isHelpScene = false;

                    INPUT->ButtonDown(false);
                }
                for (int i = 0; i < 4; i++) {
                    if (m_Button[i]->A - int(200 * dt) > 0)
                        m_Button[i]->A -= int(200 * dt);
                    else
                        m_Button[i]->A = 0;
                }
                if (m_Title->A - int(200 * dt) > 0)
                    m_Title->A -= int(200 * dt);
                else
                    m_Title->A = 0;
            }
            else if (!isHelpScene && !isRankScene) {
                for (int i = 0; i < 4; i++) {
                    if (m_Button[i]->A + int(200 * dt) < 255)
                        m_Button[i]->A += int(200 * dt);
                    else
                        m_Button[i]->A = 255;
                }
                if (m_Title->A + int(200 * dt) < 255)
                    m_Title->A += int(200 * dt);
                else
                    m_Title->A = 255;
            }
            //게임시작, 게임소개, 게임방법, 게임랭킹(score), 크래딧(credit)
            if (!isRankScene && !isHelpScene) {
                if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[0]) && INPUT->GetButtonDown())
                {
                    isMovePlayer = true;
                    INPUT->ButtonDown(false);
                }
                else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[1]) && INPUT->GetButtonDown())
                {
                    isRankScene = true;
                    RankScene->m_Visible = true;
                    GameInfo->SortRanking();
                    INPUT->ButtonDown(false);
                }
                else if (CollisionMgr::GetInst()->MouseWithBoxSize(m_Button[2]) && INPUT->GetButtonDown())
                {
                    isHelpScene = true;
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
    RankScene->Render();
    HelpScene->Render();

    if (isRankScene)
        RankRender();
}

void MainScene::BGInit()
{
    for (int i = 0; i < 6; i++) {
        m_BackGround[i][0] = Sprite::Create(L"Painting/GameScreen/Stage1/" + std::to_wstring(i) + L".png");
        m_BackGround[i][0]->SetPosition(1920 / 2 +0.1f, 1080 / 2);
        m_BackGround[i][1] = Sprite::Create(L"Painting/GameScreen/Stage1/" + std::to_wstring(i) + L".png");
        m_BackGround[i][1]->SetPosition(m_BackGround[i][0]->m_Position.x + 1920 - 0.1f, 1080 / 2);
        m_BackGround[i][0]->SetScale(1, 1);
        m_BackGround[i][1]->SetScale(1, 1);
    }
}

void MainScene::MoveBG()
{
    float bgspeed = 1;
    if (INPUT->GetKey('T') == KeyState::PRESS)
        bgspeed = 10.f;
    else
        bgspeed = 1.f;
    for (int i = 0; i < 2; i++) {
        m_BackGround[5][1 - i]->m_Position.x -= 10 * bgspeed * dt;
        m_BackGround[4][1 - i]->m_Position.x -= 15 * bgspeed * dt;
        m_BackGround[3][1 - i]->m_Position.x -= 25 * bgspeed * dt;
        m_BackGround[2][1 - i]->m_Position.x -= 50 * bgspeed * dt;
        m_BackGround[1][1 - i]->m_Position.x -= 75 * bgspeed * dt;
        m_BackGround[0][1 - i]->m_Position.x -= 100 * bgspeed * dt;
    }
}

void MainScene::ResetBG()
{
    for (int i = 0; i < 5; i++) {
        if (m_BackGround[i][0]->m_Position.x <= -1920 / 2) {
            m_BackGround[i][0]->m_Position.x = m_BackGround[i][0]->m_Position.x + m_BackGround[0][0]->m_Size.x * 2;
        }
        else if (m_BackGround[i][1]->m_Position.x <= -1920 / 2) {
            m_BackGround[i][1]->m_Position.x = m_BackGround[i][1]->m_Position.x + m_BackGround[0][1]->m_Size.x * 2;
        }
    }
}

void MainScene::RankRender()
{
    Renderer::GetInst()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);
    std::vector<RankingPlayer*> s = GameInfo->Ranks;
    m_RankText->print("(1) NAME : " + GameInfo->Ranks.at(0)->name + " / SCORE : " + std::to_string(GameInfo->Ranks.at(0)->score), 300, 300);
    m_RankText->print("(2) NAME : " + GameInfo->Ranks.at(1)->name + " / SCORE : " + std::to_string(GameInfo->Ranks.at(1)->score), 300, 400);
    m_RankText->print("(3) NAME : " + GameInfo->Ranks.at(2)->name + " / SCORE : " + std::to_string(GameInfo->Ranks.at(2)->score), 300, 500);
    if (GameInfo->Ranks.at(2)->score > GameInfo->m_Rank->score)
        m_RankText->print("(?) NAME : " + GameInfo->m_Rank->name + " / SCORE : " + std::to_string(GameInfo->m_Rank->score), 300, 650);
    Renderer::GetInst()->GetSprite()->End();

}
