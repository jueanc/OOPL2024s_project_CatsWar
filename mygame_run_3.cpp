#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "./Source/Game/mygame.h"
#include "../../monster.h"
#include <string>
#include <ctime>
#include "../../stage.h"
using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun_3::CGameStateRun_3(CGame *g) : CGameState(g)
{
}

CGameStateRun_3::~CGameStateRun_3()
{
}

void CGameStateRun_3::OnBeginState()
{
	times = 0;
	money = 0;
	money_persecond = 6;
	money_30 = 0;
	debug_mode = 0;
	enemy = 0;

	if (getStage() == 1) {
		max_money_30 = 100;
		character_call_cat_2.SetFrameIndexOfBitmap(3);
		character_call_cat_3.SetFrameIndexOfBitmap(3);
		character_call_cat_4.SetFrameIndexOfBitmap(3);
		character_call_cat_5.SetFrameIndexOfBitmap(3);
	}
	if (getStage() == 2) {
		max_money_30 = 250;
		character_call_cat_3.SetFrameIndexOfBitmap(3);
		character_call_cat_4.SetFrameIndexOfBitmap(3);
		character_call_cat_5.SetFrameIndexOfBitmap(3);
	}
	if (getStage() == 3) {
		max_money_30 = 300;
		character_call_cat_4.SetFrameIndexOfBitmap(3);
		character_call_cat_5.SetFrameIndexOfBitmap(3);
	}
	if (getStage() == 4) {
		max_money_30 = 500;
		character_call_cat_5.SetFrameIndexOfBitmap(3);
	}
	if (getStage() == 5) {
		max_money_30 = 850;
	}
	now_Level = 1;
	Level_dark.SetFrameIndexOfBitmap(0);

	current_cat_1 = 0;
	current_enemy_1 = 0;
	dog_number = 0;

	enemy_one_v.clear();
	enemy_one_v_back.clear();
	enemy_one_v_death.clear();
	enemy_one_v_if_death.clear();

	cat_one_friend.clear();
	cat_one_friend_back.clear();
	cat_one_friend_death.clear();
	cat_one_friend_if_death.clear();

	friend_tower = 1000;
	enemy_tower = 500;

	if (getStage() == 2) {
		friend_tower = 1000;
		enemy_tower = 800;
	}
	if (getStage() == 3) {
		friend_tower = 1000;
		enemy_tower = 1000;
	}
	if (getStage() == 4) {
		friend_tower = 1000;
		enemy_tower = 1500;
	}
	if (getStage() == 5) {
		friend_tower = 1500;
		enemy_tower = 1500;
	}
	cat_1_cool.SetFrameIndexOfBitmap(24);
	cat_2_cool.SetFrameIndexOfBitmap(24);
	cat_3_cool.SetFrameIndexOfBitmap(24);
	cat_4_cool.SetFrameIndexOfBitmap(24);
	cat_5_cool.SetFrameIndexOfBitmap(24);

	character_tower_2.SetFrameIndexOfBitmap(getStage() - 1);
}

void game_framework::CGameStateRun_3::OnInit()
{

	background.LoadBitmapByString({
		"resources/game_background_1.bmp"        // 載入關卡背景
		});
	background.SetTopLeft(0, 0);

	money_map.LoadBitmapByString({
		"resources/money.bmp"
		}, RGB(255, 255, 255));
	money_map.SetTopLeft(1505, 10);

	////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	Level_dark.LoadBitmapByString({
		"resources/Level_1_dark.bmp" , "resources/Level_2_dark.bmp" , "resources/Level_3_dark.bmp" ,
		"resources/Level_4_dark.bmp" , "resources/Level_5_dark.bmp" , "resources/Level_6_dark.bmp" ,
		"resources/Level_7_dark.bmp" , "resources/Level_8.bmp"
		}, RGB(255, 255, 255));
	Level_dark.SetTopLeft(50, 636);

	Level_shine[0].LoadBitmapByString({
		"resources/Level_1_shine_1.bmp" , "resources/Level_1_shine_2.bmp"
		}, RGB(255, 255, 255));
	Level_shine[0].SetTopLeft(50, 636);

	Level_shine[1].LoadBitmapByString({
		"resources/Level_2_shine_1.bmp" , "resources/Level_2_shine_2.bmp"
		}, RGB(255, 255, 255));
	Level_shine[1].SetTopLeft(50, 636);

	Level_shine[2].LoadBitmapByString({
		"resources/Level_3_shine_1.bmp" , "resources/Level_3_shine_2.bmp"
		}, RGB(255, 255, 255));
	Level_shine[2].SetTopLeft(50, 636);

	Level_shine[3].LoadBitmapByString({
		"resources/Level_4_shine_1.bmp" , "resources/Level_4_shine_2.bmp"
		}, RGB(255, 255, 255));
	Level_shine[3].SetTopLeft(50, 636);

	Level_shine[4].LoadBitmapByString({
		"resources/Level_5_shine_1.bmp" , "resources/Level_5_shine_2.bmp"
		}, RGB(255, 255, 255));
	Level_shine[4].SetTopLeft(50, 636);

	Level_shine[5].LoadBitmapByString({
		"resources/Level_6_shine_1.bmp" , "resources/Level_6_shine_2.bmp"
		}, RGB(255, 255, 255));
	Level_shine[5].SetTopLeft(50, 636);

	Level_shine[6].LoadBitmapByString({
		"resources/Level_7_shine_1.bmp" , "resources/Level_7_shine_2.bmp"
		}, RGB(255, 255, 255));
	Level_shine[6].SetTopLeft(50, 636);
	////////////////////////////////////////////////////////////////////////////////////////////////

	character_call_cat_1.LoadBitmapByString({
		"resources/call_cat_2.bmp" , "resources/call_cat_1.bmp" , "resources/call_cat_load.bmp"    , "resources/call_cat_empty.bmp"    // 載入招喚貓咪1按鈕
		}, RGB(255, 255, 255));
	character_call_cat_1.SetTopLeft(470, 680);
	character_call_cat_1.SetFrameIndexOfBitmap(1);

	cat_1_cool.LoadBitmapByString({
		"resources/load_1.bmp" , "resources/load_2.bmp" , "resources/load_3.bmp" ,
		"resources/load_4.bmp" , "resources/load_5.bmp" , "resources/load_6.bmp" ,
		"resources/load_7.bmp" , "resources/load_8.bmp" , "resources/load_9.bmp" ,
		"resources/load_10.bmp" , "resources/load_11.bmp" , "resources/load_12.bmp" ,
		"resources/load_13.bmp" , "resources/load_14.bmp" , "resources/load_15.bmp" ,
		"resources/load_16.bmp" , "resources/load_17.bmp" , "resources/load_18.bmp" ,
		"resources/load_19.bmp" , "resources/load_20.bmp" , "resources/load_21.bmp" ,
		"resources/load_22.bmp" , "resources/load_23.bmp" , "resources/load_24.bmp" ,
		"resources/load_25.bmp"
		}, RGB(255, 255, 255));
	cat_1_cool.SetTopLeft(477, 757);
	cat_1_cool.SetFrameIndexOfBitmap(24);
////2
	character_call_cat_2.LoadBitmapByString({
		"resources/call_longcat_2.bmp" , "resources/call_longcat_1.bmp" , "resources/call_longcat_load.bmp"   , "resources/call_cat_empty.bmp"     // 載入召喚貓咪2(空)按鈕
		}, RGB(255, 255, 255));
	character_call_cat_2.SetTopLeft(625, 680);
	character_call_cat_2.SetFrameIndexOfBitmap(1);

	cat_2_cool.LoadBitmapByString({
		"resources/load_1.bmp" , "resources/load_2.bmp" , "resources/load_3.bmp" ,
		"resources/load_4.bmp" , "resources/load_5.bmp" , "resources/load_6.bmp" ,
		"resources/load_7.bmp" , "resources/load_8.bmp" , "resources/load_9.bmp" ,
		"resources/load_10.bmp" , "resources/load_11.bmp" , "resources/load_12.bmp" ,
		"resources/load_13.bmp" , "resources/load_14.bmp" , "resources/load_15.bmp" ,
		"resources/load_16.bmp" , "resources/load_17.bmp" , "resources/load_18.bmp" ,
		"resources/load_19.bmp" , "resources/load_20.bmp" , "resources/load_21.bmp" ,
		"resources/load_22.bmp" , "resources/load_23.bmp" , "resources/load_24.bmp" ,
		"resources/load_25.bmp"
		}, RGB(255, 255, 255));
	cat_2_cool.SetTopLeft(632, 757);
	cat_2_cool.SetFrameIndexOfBitmap(24);
////3
	character_call_cat_3.LoadBitmapByString({
		"resources/call_ax_2.bmp" , "resources/call_ax_1.bmp" , "resources/call_ax_load.bmp"  , "resources/call_cat_empty.bmp"      // 載入召喚貓咪3(空)按鈕
		}, RGB(255, 255, 255));
	character_call_cat_3.SetTopLeft(780, 680);
	character_call_cat_3.SetFrameIndexOfBitmap(1);

	cat_3_cool.LoadBitmapByString({
		"resources/load_1.bmp" , "resources/load_2.bmp" , "resources/load_3.bmp" ,
		"resources/load_4.bmp" , "resources/load_5.bmp" , "resources/load_6.bmp" ,
		"resources/load_7.bmp" , "resources/load_8.bmp" , "resources/load_9.bmp" ,
		"resources/load_10.bmp" , "resources/load_11.bmp" , "resources/load_12.bmp" ,
		"resources/load_13.bmp" , "resources/load_14.bmp" , "resources/load_15.bmp" ,
		"resources/load_16.bmp" , "resources/load_17.bmp" , "resources/load_18.bmp" ,
		"resources/load_19.bmp" , "resources/load_20.bmp" , "resources/load_21.bmp" ,
		"resources/load_22.bmp" , "resources/load_23.bmp" , "resources/load_24.bmp" ,
		"resources/load_25.bmp"
		}, RGB(255, 255, 255));
	cat_3_cool.SetTopLeft(787, 757);
	cat_3_cool.SetFrameIndexOfBitmap(24);
////關卡4

	character_call_cat_4.LoadBitmapByString({
		"resources/call_ba_2.bmp" , "resources/call_ba_1.bmp" , "resources/call_ba_load.bmp"  , "resources/call_cat_empty.bmp"      // 載入召喚貓2(空)按鈕
		});
	character_call_cat_4.SetTopLeft(935, 680);
	character_call_cat_4.SetFrameIndexOfBitmap(1);

	cat_4_cool.LoadBitmapByString({
		"resources/load_1.bmp" , "resources/load_2.bmp" , "resources/load_3.bmp" ,
		"resources/load_4.bmp" , "resources/load_5.bmp" , "resources/load_6.bmp" ,
		"resources/load_7.bmp" , "resources/load_8.bmp" , "resources/load_9.bmp" ,
		"resources/load_10.bmp" , "resources/load_11.bmp" , "resources/load_12.bmp" ,
		"resources/load_13.bmp" , "resources/load_14.bmp" , "resources/load_15.bmp" ,
		"resources/load_16.bmp" , "resources/load_17.bmp" , "resources/load_18.bmp" ,
		"resources/load_19.bmp" , "resources/load_20.bmp" , "resources/load_21.bmp" ,
		"resources/load_22.bmp" , "resources/load_23.bmp" , "resources/load_24.bmp" ,
		"resources/load_25.bmp"
		}, RGB(255, 255, 255));
	cat_4_cool.SetTopLeft(942, 757);
	cat_4_cool.SetFrameIndexOfBitmap(24);

////5

	character_call_cat_5.LoadBitmapByString({
		"resources/call_bi_2.bmp" , "resources/call_bi_1.bmp" , "resources/call_bi_load.bmp"  , "resources/call_cat_empty.bmp"
		});
	character_call_cat_5.SetTopLeft(1090, 680);
	character_call_cat_5.SetFrameIndexOfBitmap(1);

	cat_5_cool.LoadBitmapByString({
		"resources/load_1.bmp" , "resources/load_2.bmp" , "resources/load_3.bmp" ,
		"resources/load_4.bmp" , "resources/load_5.bmp" , "resources/load_6.bmp" ,
		"resources/load_7.bmp" , "resources/load_8.bmp" , "resources/load_9.bmp" ,
		"resources/load_10.bmp" , "resources/load_11.bmp" , "resources/load_12.bmp" ,
		"resources/load_13.bmp" , "resources/load_14.bmp" , "resources/load_15.bmp" ,
		"resources/load_16.bmp" , "resources/load_17.bmp" , "resources/load_18.bmp" ,
		"resources/load_19.bmp" , "resources/load_20.bmp" , "resources/load_21.bmp" ,
		"resources/load_22.bmp" , "resources/load_23.bmp" , "resources/load_24.bmp" ,
		"resources/load_25.bmp"
		}, RGB(255, 255, 255));
	cat_5_cool.SetTopLeft(1097, 757);
	cat_5_cool.SetFrameIndexOfBitmap(24);
////

	character_tower_1.LoadBitmapByString({
		"resources/tower_0.bmp"        // 載入己方防禦塔
		}, RGB(255, 255, 255));
	character_tower_1.SetTopLeft(1400, 175);

	character_tower_2.LoadBitmapByString({
		"resources/tower_1.bmp" , "resources/tower_2.bmp"  , "resources/tower_3.bmp" , "resources/tower_4.bmp" , "resources/tower_5.bmp"            // 載入敵方防禦塔
		}, RGB(255, 255, 255));
	character_tower_2.SetTopLeft(100, 163);	

	
	


	esc.LoadBitmapByString({
		"resources/esc.bmp"       
		}, RGB(255, 255, 255));
	esc.SetTopLeft(0, 0);
	/*


	*/
	base_1 = monster(1);
	base_2 = monster(2);
	base_3 = monster(3);
	base_4 = monster(4);
	base_5 = monster(5);

	base_11 = monster(11);
	base_12 = monster(12);
	friend_tower = 1000;
	enemy_tower = 500;
	debug_mode = 0;
}

void CGameStateRun_3::OnMove()							// 移動遊戲元素
{
	/////////////////////////////////////
	// 設定敵對生物及貓咪移動停止參數
	/////////////////////////////////////
	for (int d = 0; d < enemy_one_v.size(); d++) {
		int t = 0;
		for (int i = 0; i < cat_one_friend.size(); i++) {
			if (enemy_one_v[d].GetLeft() + 50 + enemy_one_v[d].GetWidth() < cat_one_friend[i].GetLeft() || cat_one_friend_if_death[i]) {
				t += 1;
			}
		}
		if ((t == cat_one_friend.size() || cat_one_friend.size() == 0) && enemy_one_v[d].GetLeft() + 50 + enemy_one_v[d].GetWidth() < character_tower_1.GetLeft() && enemy_one_v[d].get_type() != 2 && !(enemy_one_v_if_death[d])) {
			enemy_one_v[d].SetTopLeft(enemy_one_v[d].GetLeft() + 1, enemy_one_v[d].GetTop());
		}
		else {
			enemy_one_v[d].SetFrameIndexOfBitmap(1);
		}
	}

	for (int i = 0; i < cat_one_friend.size(); i++) {
		int t = 0;
		for (int d = 0; d < enemy_one_v.size(); d++) {
			if (enemy_one_v[d].GetLeft() + 50 + enemy_one_v[d].GetWidth() < cat_one_friend[i].GetLeft() || enemy_one_v_if_death[d]) {
				t += 1;
			}
		}
		if ((t == enemy_one_v.size() || enemy_one_v.size() == 0) && cat_one_friend[i].GetLeft() > character_tower_2.GetLeft() + 50 + character_tower_2.GetWidth() && cat_one_friend[i].get_type() != 2) {
			cat_one_friend[i].SetTopLeft(cat_one_friend[i].GetLeft() - cat_one_friend[i].get_walk_speed(), cat_one_friend[i].GetTop());
		}
		else {
			cat_one_friend[i].SetFrameIndexOfBitmap(1);
		}
	}
	// 錢
	if (debug_mode == 1) {
		money = max_money_30 * 30;
	}else if (money_30 < max_money_30) {
		money += money_persecond;
	}
	money_30 = money / 30;

	if (money_30 >= base_1.get_price() && cat_1_cool.GetFrameIndexOfBitmap() == 24 && getStage() >= 1) {
		character_call_cat_1.SetFrameIndexOfBitmap(0);

	}
	if (money_30 >= base_2.get_price() && cat_2_cool.GetFrameIndexOfBitmap() == 24 && getStage() >= 2) {
		character_call_cat_2.SetFrameIndexOfBitmap(0);
	}
	if (money_30 >= base_3.get_price() && cat_3_cool.GetFrameIndexOfBitmap() == 24 && getStage() >= 3) {
		character_call_cat_3.SetFrameIndexOfBitmap(0);
	}
	if (money_30 >= base_4.get_price() && cat_4_cool.GetFrameIndexOfBitmap() == 24 && getStage() >= 4) {
		character_call_cat_4.SetFrameIndexOfBitmap(0);
	}
	if (money_30 >= base_5.get_price() && cat_5_cool.GetFrameIndexOfBitmap() == 24 && getStage() >= 5) {
		character_call_cat_5.SetFrameIndexOfBitmap(0);
	}

	///////////////////////
	// 敵對生物自動生成
	///////////////////////
	//接下來的程式碼事進行關卡的部分
	if (enemy % 360 == 0 && enemy >= 1) {        // 計數達指定次數生成敵對生物
		enemy_one_v_if_death.push_back(false);

		monster enemy1(11);
		enemy_one_v.push_back(enemy1);
		enemy_one_v[enemy_one_v.size() - 1].LoadBitmapByString({
		"resources/dog/walk_1.bmp" , "resources/dog/walk_2.bmp" , "resources/dog/walk_3.bmp" , "resources/dog/walk_2.bmp"        // 載入敵對狗走路動畫
			}, RGB(255, 255, 255));
		enemy_one_v[enemy_one_v.size() - 1].SetTopLeft(170, 430);
		enemy_one_v[enemy_one_v.size() - 1].SetAnimation(250, 0);

		enemy_one_v[enemy_one_v.size() - 1].attack.LoadBitmapByString({
		"resources/dog/attack_1.bmp" , "resources/dog/attack_2.bmp" , "resources/dog/attack_1.bmp" ,
		"resources/dog/attack_3.bmp" , "resources/dog/attack_3.bmp" , "resources/dog/attack_3.bmp" ,
		"resources/dog/attack_3.bmp" , "resources/dog/attack_3.bmp" , "resources/dog/walk_2.bmp" ,
		"resources/dog/walk_2.bmp" , "resources/dog/walk_2.bmp" , "resources/dog/walk_2.bmp" ,
		"resources/dog/walk_2.bmp" , "resources/dog/walk_2.bmp" , "resources/dog/walk_2.bmp" ,
		"resources/dog/walk_2.bmp" , "resources/dog/walk_2.bmp" , "resources/dog/walk_2.bmp"        // 載入敵對狗攻擊動畫
			}, RGB(255, 255, 255));

		enemy_one_v[enemy_one_v.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1_inverse.bmp" , "resources/bump_2_inverse.bmp" , "resources/bump_3_inverse.bmp" ,
		"resources/bump_4_inverse.bmp" , "resources/bump_5_inverse.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入敵對狗攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster enemy1_back(11);
		enemy_one_v_back.push_back(enemy1_back);
		enemy_one_v_back[enemy_one_v_back.size() - 1].LoadBitmapByString({
		"resources/dog/back_0.bmp" , "resources/dog/back_1.bmp" , "resources/dog/back_2.bmp" ,
		"resources/dog/back_3.bmp" , "resources/dog/back_4.bmp" , "resources/dog/back_5.bmp" ,
		"resources/dog/back_6.bmp" , "resources/dog/back_7.bmp" , "resources/dog/back_8.bmp" ,
		"resources/dog/back_9.bmp" , "resources/dog/back_10.bmp" , "resources/dog/back_11.bmp" ,
		"resources/dog/back_12.bmp" , "resources/dog/back_13.bmp" , "resources/dog/back_14.bmp" ,
		"resources/dog/back_15.bmp" , "resources/dog/back_16.bmp" , "resources/dog/back_17.bmp" ,
		"resources/dog/back_18.bmp" , "resources/dog/back_19.bmp" , "resources/dog/back_20.bmp" ,
		"resources/dog/back_21.bmp" , "resources/dog/back_22.bmp" , "resources/dog/back_23.bmp" ,
		"resources/dog/back_24.bmp" , "resources/dog/back_25.bmp" , "resources/dog/back_26.bmp" ,
		"resources/dog/back_27.bmp" , "resources/dog/back_28.bmp" , "resources/dog/back_29.bmp" ,
		"resources/dog/back_30.bmp" , "resources/dog/back_31.bmp" , "resources/dog/back_32.bmp" ,
		"resources/dog/back_33.bmp" , "resources/dog/back_34.bmp" , "resources/dog/back_35.bmp"
			}, RGB(255, 255, 255));

		monster enemy1_death(11);
		enemy_one_v_death.push_back(enemy1_death);
		enemy_one_v_death[enemy_one_v_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
		/*
		dog_number += 1;
		if (dog_number == 2) {
			enemy = 0;        // 計數歸零
			dog_number = 0;
		}		
		*/

		if (enemy >3000) {
			enemy = 0;        // 計數歸零

		}
	}

	if (enemy % 750 == 0 && enemy > 0 && getStage() >= 2) {      
		enemy_one_v_if_death.push_back(false);

		monster enemy1(12);
		enemy_one_v.push_back(enemy1);
		enemy_one_v[enemy_one_v.size() - 1].LoadBitmapByString({
		"resources/snake/walk_1.bmp" , "resources/snake/walk_2.bmp" , "resources/snake/walk_3.bmp" , "resources/snake/walk_2.bmp"        // 載入敵對狗走路動畫
			}, RGB(255, 255, 255));
		enemy_one_v[enemy_one_v.size() - 1].SetTopLeft(170, 420);
		enemy_one_v[enemy_one_v.size() - 1].SetAnimation(250, 0);

		enemy_one_v[enemy_one_v.size() - 1].attack.LoadBitmapByString({
		"resources/snake/attack_1.bmp" , "resources/snake/attack_2.bmp" , "resources/snake/attack_1.bmp" ,
		"resources/snake/attack_3.bmp" , "resources/snake/attack_3.bmp" , "resources/snake/attack_3.bmp" ,
		"resources/snake/attack_3.bmp" , "resources/snake/attack_3.bmp" , "resources/snake/walk_2.bmp" ,
		"resources/snake/walk_2.bmp" , "resources/snake/walk_2.bmp" , "resources/snake/walk_2.bmp" ,
		"resources/snake/walk_2.bmp" , "resources/snake/walk_2.bmp" , "resources/snake/walk_2.bmp" ,
		"resources/snake/walk_2.bmp" , "resources/snake/walk_2.bmp" , "resources/snake/walk_2.bmp"        // 載入敵對狗攻擊動畫
			}, RGB(255, 255, 255));

		enemy_one_v[enemy_one_v.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1_inverse.bmp" , "resources/bump_2_inverse.bmp" , "resources/bump_3_inverse.bmp" ,
		"resources/bump_4_inverse.bmp" , "resources/bump_5_inverse.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入敵對狗攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster enemy1_back(12);
		enemy_one_v_back.push_back(enemy1_back);
		enemy_one_v_back[enemy_one_v_back.size() - 1].LoadBitmapByString({
		"resources/snake/back_0.bmp" , "resources/snake/back_1.bmp" , "resources/snake/back_2.bmp" ,
		"resources/snake/back_3.bmp" , "resources/snake/back_4.bmp" , "resources/snake/back_5.bmp" ,
		"resources/snake/back_6.bmp" , "resources/snake/back_7.bmp" , "resources/snake/back_8.bmp" ,
		"resources/snake/back_9.bmp" , "resources/snake/back_10.bmp" , "resources/snake/back_11.bmp" ,
		"resources/snake/back_12.bmp" , "resources/snake/back_13.bmp" , "resources/snake/back_14.bmp" ,
		"resources/snake/back_15.bmp" , "resources/snake/back_16.bmp" , "resources/snake/back_17.bmp" ,
		"resources/snake/back_18.bmp" , "resources/snake/back_19.bmp" , "resources/snake/back_20.bmp" ,
		"resources/snake/back_21.bmp" , "resources/snake/back_22.bmp" , "resources/snake/back_23.bmp" ,
		"resources/snake/back_24.bmp" , "resources/snake/back_25.bmp" , "resources/snake/back_26.bmp" ,
		"resources/snake/back_27.bmp" , "resources/snake/back_28.bmp" , "resources/snake/back_29.bmp" ,
		"resources/snake/back_30.bmp" , "resources/snake/back_31.bmp" , "resources/snake/back_32.bmp" ,
		"resources/snake/back_33.bmp" , "resources/snake/back_34.bmp" , "resources/snake/back_35.bmp" ,
			}, RGB(255, 255, 255));

		monster enemy1_death(12);
		enemy_one_v_death.push_back(enemy1_death);
		enemy_one_v_death[enemy_one_v_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}

	if (enemy % 1000 == 0 && enemy > 0 && getStage() >= 3) {        // 計數達指定次數生成敵對生物
		enemy_one_v_if_death.push_back(false);

		monster enemy1(13);
		enemy_one_v.push_back(enemy1);
		enemy_one_v[enemy_one_v.size() - 1].LoadBitmapByString({
		"resources/people/walk_1.bmp" , "resources/people/walk_2.bmp" , "resources/people/walk_3.bmp" , "resources/people/walk_2.bmp"        // 載入敵對狗走路動畫
			}, RGB(255, 255, 255));
		enemy_one_v[enemy_one_v.size() - 1].SetTopLeft(170, 500);
		enemy_one_v[enemy_one_v.size() - 1].SetAnimation(250, 0);

		enemy_one_v[enemy_one_v.size() - 1].attack.LoadBitmapByString({
		"resources/people/attack_1.bmp" , "resources/people/attack_2.bmp" , "resources/people/attack_1.bmp" ,
		"resources/people/attack_3.bmp" , "resources/people/attack_3.bmp" , "resources/people/attack_3.bmp" ,
		"resources/people/attack_3.bmp" , "resources/people/attack_3.bmp" , "resources/people/walk_2.bmp" ,
		"resources/people/walk_2.bmp" , "resources/people/walk_2.bmp" , "resources/people/walk_2.bmp" ,
		"resources/people/walk_2.bmp" , "resources/people/walk_2.bmp" , "resources/people/walk_2.bmp" ,
		"resources/people/walk_2.bmp" , "resources/people/walk_2.bmp" , "resources/people/walk_2.bmp"        // 載入敵對狗攻擊動畫
			}, RGB(255, 255, 255));

		enemy_one_v[enemy_one_v.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1_inverse.bmp" , "resources/bump_2_inverse.bmp" , "resources/bump_3_inverse.bmp" ,
		"resources/bump_4_inverse.bmp" , "resources/bump_5_inverse.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入敵對狗攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster enemy1_back(13);
		enemy_one_v_back.push_back(enemy1_back);
		enemy_one_v_back[enemy_one_v_back.size() - 1].LoadBitmapByString({
		"resources/people/back_0.bmp" , "resources/people/back_1.bmp" , "resources/people/back_2.bmp" ,
		"resources/people/back_3.bmp" , "resources/people/back_4.bmp" , "resources/people/back_5.bmp" ,
		"resources/people/back_6.bmp" , "resources/people/back_7.bmp" , "resources/people/back_8.bmp" ,
		"resources/people/back_9.bmp" , "resources/people/back_10.bmp" , "resources/people/back_11.bmp" ,
		"resources/people/back_12.bmp" , "resources/people/back_13.bmp" , "resources/people/back_14.bmp" ,
		"resources/people/back_15.bmp" , "resources/people/back_16.bmp" , "resources/people/back_17.bmp" ,
		"resources/people/back_18.bmp" , "resources/people/back_19.bmp" , "resources/people/back_20.bmp" ,
		"resources/people/back_21.bmp" , "resources/people/back_22.bmp" , "resources/people/back_23.bmp" ,
		"resources/people/back_24.bmp" , "resources/people/back_25.bmp" , "resources/people/back_26.bmp" ,
		"resources/people/back_27.bmp" , "resources/people/back_28.bmp" , "resources/people/back_29.bmp" ,
		"resources/people/back_30.bmp" , "resources/people/back_31.bmp" , "resources/people/back_32.bmp" ,
		"resources/people/back_33.bmp" , "resources/people/back_34.bmp" , "resources/people/back_35.bmp" ,
			}, RGB(255, 255, 255));

		monster enemy1_death(13);
		enemy_one_v_death.push_back(enemy1_death);
		enemy_one_v_death[enemy_one_v_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}

	if (enemy % 2200 == 0 && enemy > 0 && getStage() >= 4) {        // 計數達指定次數生成敵對生物
		enemy_one_v_if_death.push_back(false);

		monster enemy1(14);
		enemy_one_v.push_back(enemy1);
		enemy_one_v[enemy_one_v.size() - 1].LoadBitmapByString({
		"resources/pig/walk_1.bmp" , "resources/pig/walk_2.bmp" , "resources/pig/walk_3.bmp" , "resources/pig/walk_2.bmp"        // 載入敵對狗走路動畫
			}, RGB(255, 0, 0));
		enemy_one_v[enemy_one_v.size() - 1].SetTopLeft(60, 325);
		enemy_one_v[enemy_one_v.size() - 1].SetAnimation(250, 0);

		enemy_one_v[enemy_one_v.size() - 1].attack.LoadBitmapByString({
		"resources/pig/attack_1.bmp" , "resources/pig/attack_2.bmp" , "resources/pig/attack_1.bmp" ,
		"resources/pig/attack_3.bmp" , "resources/pig/attack_3.bmp" , "resources/pig/attack_3.bmp" ,
		"resources/pig/attack_3.bmp" , "resources/pig/attack_3.bmp" , "resources/pig/walk_2.bmp" ,
		"resources/pig/walk_2.bmp" , "resources/pig/walk_2.bmp" , "resources/pig/walk_2.bmp" ,
		"resources/pig/walk_2.bmp" , "resources/pig/walk_2.bmp" , "resources/pig/walk_2.bmp" ,
		"resources/pig/walk_2.bmp" , "resources/pig/walk_2.bmp" , "resources/pig/walk_2.bmp"        // 載入敵對狗攻擊動畫
			}, RGB(255, 0, 0));

		enemy_one_v[enemy_one_v.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1_inverse.bmp" , "resources/bump_2_inverse.bmp" , "resources/bump_3_inverse.bmp" ,
		"resources/bump_4_inverse.bmp" , "resources/bump_5_inverse.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入敵對狗攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster enemy1_back(14);
		enemy_one_v_back.push_back(enemy1_back);
		enemy_one_v_back[enemy_one_v_back.size() - 1].LoadBitmapByString({
		"resources/pig/back_0.bmp" , "resources/pig/back_1.bmp" , "resources/pig/back_2.bmp" ,
		"resources/pig/back_3.bmp" , "resources/pig/back_4.bmp" , "resources/pig/back_5.bmp" ,
		"resources/pig/back_6.bmp" , "resources/pig/back_7.bmp" , "resources/pig/back_8.bmp" ,
		"resources/pig/back_9.bmp" , "resources/pig/back_10.bmp" , "resources/pig/back_11.bmp" ,
		"resources/pig/back_12.bmp" , "resources/pig/back_13.bmp" , "resources/pig/back_14.bmp" ,
		"resources/pig/back_15.bmp" , "resources/pig/back_16.bmp" , "resources/pig/back_17.bmp" ,
		"resources/pig/back_18.bmp" , "resources/pig/back_19.bmp" , "resources/pig/back_20.bmp" ,
		"resources/pig/back_21.bmp" , "resources/pig/back_22.bmp" , "resources/pig/back_23.bmp" ,
		"resources/pig/back_24.bmp" , "resources/pig/back_25.bmp" , "resources/pig/back_26.bmp" ,
		"resources/pig/back_27.bmp" , "resources/pig/back_28.bmp" , "resources/pig/back_29.bmp" ,
		"resources/pig/back_30.bmp" , "resources/pig/back_31.bmp" , "resources/pig/back_32.bmp" ,
		"resources/pig/back_33.bmp" , "resources/pig/back_34.bmp" , "resources/pig/back_35.bmp" ,
			}, RGB(255, 0, 0));

		monster enemy1_death(14);
		enemy_one_v_death.push_back(enemy1_death);
		enemy_one_v_death[enemy_one_v_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}

	if (enemy % 3000 == 0 && enemy > 0 && getStage() == 5) {        // 計數達指定次數生成敵對生物
		enemy_one_v_if_death.push_back(false);

		monster enemy1(15);
		enemy_one_v.push_back(enemy1);
		enemy_one_v[enemy_one_v.size() - 1].LoadBitmapByString({
		"resources/hippo/walk_1.bmp" , "resources/hippo/walk_2.bmp" , "resources/hippo/walk_3.bmp" , "resources/hippo/walk_2.bmp"        // 載入敵對狗走路動畫
			}, RGB(255, 0, 0));
		enemy_one_v[enemy_one_v.size() - 1].SetTopLeft(60, 395);
		enemy_one_v[enemy_one_v.size() - 1].SetAnimation(250, 0);

		enemy_one_v[enemy_one_v.size() - 1].attack.LoadBitmapByString({
		"resources/hippo/attack_1.bmp" , "resources/hippo/attack_2.bmp" , "resources/hippo/attack_1.bmp" ,
		"resources/hippo/attack_3.bmp" , "resources/hippo/attack_3.bmp" , "resources/hippo/attack_3.bmp" ,
		"resources/hippo/attack_3.bmp" , "resources/hippo/attack_3.bmp" , "resources/hippo/walk_2.bmp" ,
		"resources/hippo/walk_2.bmp" , "resources/hippo/walk_2.bmp" , "resources/hippo/walk_2.bmp" ,
		"resources/hippo/walk_2.bmp" , "resources/hippo/walk_2.bmp" , "resources/hippo/walk_2.bmp" ,
		"resources/hippo/walk_2.bmp" , "resources/hippo/walk_2.bmp" , "resources/hippo/walk_2.bmp"        // 載入敵對狗攻擊動畫
			}, RGB(255, 0, 0));

		enemy_one_v[enemy_one_v.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1_inverse.bmp" , "resources/bump_2_inverse.bmp" , "resources/bump_3_inverse.bmp" ,
		"resources/bump_4_inverse.bmp" , "resources/bump_5_inverse.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入敵對狗攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster enemy1_back(15);
		enemy_one_v_back.push_back(enemy1_back);
		enemy_one_v_back[enemy_one_v_back.size() - 1].LoadBitmapByString({
		"resources/hippo/back_0.bmp" , "resources/hippo/back_1.bmp" , "resources/hippo/back_2.bmp" ,
		"resources/hippo/back_3.bmp" , "resources/hippo/back_4.bmp" , "resources/hippo/back_5.bmp" ,
		"resources/hippo/back_6.bmp" , "resources/hippo/back_7.bmp" , "resources/hippo/back_8.bmp" ,
		"resources/hippo/back_9.bmp" , "resources/hippo/back_10.bmp" , "resources/hippo/back_11.bmp" ,
		"resources/hippo/back_12.bmp" , "resources/hippo/back_13.bmp" , "resources/hippo/back_14.bmp" ,
		"resources/hippo/back_15.bmp" , "resources/hippo/back_16.bmp" , "resources/hippo/back_17.bmp" ,
		"resources/hippo/back_18.bmp" , "resources/hippo/back_19.bmp" , "resources/hippo/back_20.bmp" ,
		"resources/hippo/back_21.bmp" , "resources/hippo/back_22.bmp" , "resources/hippo/back_23.bmp" ,
		"resources/hippo/back_24.bmp" , "resources/hippo/back_25.bmp" , "resources/hippo/back_26.bmp" ,
		"resources/hippo/back_27.bmp" , "resources/hippo/back_28.bmp" , "resources/hippo/back_29.bmp" ,
		"resources/hippo/back_30.bmp" , "resources/hippo/back_31.bmp" , "resources/hippo/back_32.bmp" ,
		"resources/hippo/back_33.bmp" , "resources/hippo/back_34.bmp" , "resources/hippo/back_35.bmp" ,
			}, RGB(255, 0, 0));

		monster enemy1_death(15);
		enemy_one_v_death.push_back(enemy1_death);
		enemy_one_v_death[enemy_one_v_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}
	enemy += 1;        // 時間計數每秒+30
}

void CGameStateRun_3::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) // 按esc快速返回
{
	if (nChar == VK_ESCAPE && debug_mode == 1) {
		GotoGameState(GAME_STATE_RUN);
	}
	if (nChar == VK_UP) {
		if (debug_mode == 0)
		{
			debug_mode = 1;
		}
		else {
			debug_mode = 0;
		}
	}
}

void CGameStateRun_3::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{

}

void CGameStateRun_3::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	///////////////////////////////////
	// 藉由點擊次數生成相應數量貓咪
	///////////////////////////////////

	if (point.x >= 470 && point.x <= 614 && point.y >= 680 && point.y <= 789 && money_30 >= base_1.get_price() && (cat_1_cool.GetFrameIndexOfBitmap() == 24 || debug_mode == 1) && getStage() >= 1) {
		money_30 = money_30 - base_1.get_price();
		money = money - (base_1.get_price() * 30);
		if (debug_mode == 0) {
			character_call_cat_1.SetFrameIndexOfBitmap(2);
			cat_1_cool.SetFrameIndexOfBitmap(0);
			cat_1_cool.SetAnimation(250, 0);
		}
		cat_one_friend_if_death.push_back(false);

		monster temp1(1);
		cat_one_friend.push_back(temp1);
		cat_one_friend[cat_one_friend.size() - 1].LoadBitmapByString({
		"resources/cat/walk_1.bmp" , "resources/cat/walk_2.bmp" , "resources/cat/walk_3.bmp" , "resources/cat/walk_2.bmp"        // 載入貓咪1走路動畫
			}, RGB(255, 255, 255));
		cat_one_friend[cat_one_friend.size() - 1].SetTopLeft(1400, 430);
		cat_one_friend[cat_one_friend.size() - 1].SetAnimation(125, 0);

		cat_one_friend[cat_one_friend.size() - 1].attack.LoadBitmapByString({
		"resources/cat/attack_1.bmp" , "resources/cat/attack_2.bmp" , "resources/cat/attack_1.bmp" ,
		"resources/cat/attack_3.bmp" , "resources/cat/attack_3.bmp" , "resources/cat/attack_3.bmp" ,
		"resources/cat/attack_3.bmp" , "resources/cat/attack_3.bmp" , "resources/cat/walk_2.bmp" ,
		"resources/cat/walk_2.bmp" , "resources/cat/walk_2.bmp" , "resources/cat/walk_2.bmp"        // 載入貓咪1攻擊動畫
			}, RGB(255, 255, 255));

		cat_one_friend[cat_one_friend.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1.bmp" , "resources/bump_2.bmp" , "resources/bump_3.bmp" ,
		"resources/bump_4.bmp" , "resources/bump_5.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入貓咪1攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster back1(1);
		cat_one_friend_back.push_back(back1);
		cat_one_friend_back[cat_one_friend_back.size() - 1].LoadBitmapByString({
		"resources/cat/back_0.bmp" , "resources/cat/back_1.bmp" , "resources/cat/back_2.bmp" ,
		"resources/cat/back_3.bmp" , "resources/cat/back_4.bmp" , "resources/cat/back_5.bmp" ,
		"resources/cat/back_6.bmp" , "resources/cat/back_7.bmp" , "resources/cat/back_8.bmp" ,
		"resources/cat/back_9.bmp" , "resources/cat/back_10.bmp" , "resources/cat/back_11.bmp" ,
		"resources/cat/back_12.bmp" , "resources/cat/back_13.bmp" , "resources/cat/back_14.bmp" ,
		"resources/cat/back_15.bmp" , "resources/cat/back_16.bmp" , "resources/cat/back_17.bmp" ,
		"resources/cat/back_18.bmp" , "resources/cat/back_19.bmp" , "resources/cat/back_20.bmp" ,
		"resources/cat/back_21.bmp" , "resources/cat/back_22.bmp" , "resources/cat/back_23.bmp" ,
		"resources/cat/back_24.bmp" , "resources/cat/back_25.bmp" , "resources/cat/back_26.bmp" ,
		"resources/cat/back_27.bmp" , "resources/cat/back_28.bmp" , "resources/cat/back_29.bmp" ,
		"resources/cat/back_30.bmp" , "resources/cat/back_31.bmp" , "resources/cat/back_32.bmp" ,
		"resources/cat/back_33.bmp" , "resources/cat/back_34.bmp" , "resources/cat/back_35.bmp"
			}, RGB(255, 255, 255));

		monster death1(1);
		cat_one_friend_death.push_back(death1);
		cat_one_friend_death[cat_one_friend_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}
	////2
	if (point.x >= 625 && point.x <= 769 && point.y >= 680 && point.y <= 789 && money_30 >= base_2.get_price() && (cat_2_cool.GetFrameIndexOfBitmap() == 24 || debug_mode == 1) && getStage() >= 2) {
		money_30 = money_30 - base_2.get_price();
		money = money - (base_2.get_price() * 30);
		if (debug_mode == 0) {
			character_call_cat_2.SetFrameIndexOfBitmap(2);
			cat_2_cool.SetFrameIndexOfBitmap(0);
			cat_2_cool.SetAnimation(250, 0);
		}
		cat_one_friend_if_death.push_back(false);

		monster temp2(2);
		cat_one_friend.push_back(temp2);
		cat_one_friend[cat_one_friend.size() - 1].LoadBitmapByString({
		"resources/long/walk_1.bmp" , "resources/long/walk_2.bmp" , "resources/long/walk_3.bmp" , "resources/long/walk_2.bmp"        // 載入貓咪2走路動畫
			}, RGB(255, 255, 255));
		cat_one_friend[cat_one_friend.size() - 1].SetTopLeft(1350, 345);
		cat_one_friend[cat_one_friend.size() - 1].SetAnimation(125, 0);

		cat_one_friend[cat_one_friend.size() - 1].attack.LoadBitmapByString({
		"resources/long/attack_1.bmp" , "resources/long/attack_2.bmp" , "resources/long/attack_1.bmp" ,
		"resources/long/attack_3.bmp" , "resources/long/attack_4.bmp" , "resources/long/attack_4.bmp" ,
		"resources/long/attack_4.bmp" , "resources/long/attack_4.bmp" , "resources/long/walk_2.bmp" ,
		"resources/long/walk_2.bmp" , "resources/long/walk_2.bmp" , "resources/long/walk_2.bmp"        // 載入貓咪2攻擊動畫
			}, RGB(255, 255, 255));

		cat_one_friend[cat_one_friend.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1.bmp" , "resources/bump_2.bmp" , "resources/bump_3.bmp" ,
		"resources/bump_4.bmp" , "resources/bump_5.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入貓咪2攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster back2(2);
		cat_one_friend_back.push_back(back2);
		cat_one_friend_back[cat_one_friend_back.size() - 1].LoadBitmapByString({
		"resources/long/back_0.bmp" , "resources/long/back_1.bmp" , "resources/long/back_2.bmp" ,
		"resources/long/back_3.bmp" , "resources/long/back_4.bmp" , "resources/long/back_5.bmp" ,
		"resources/long/back_6.bmp" , "resources/long/back_7.bmp" , "resources/long/back_8.bmp" ,
		"resources/long/back_9.bmp" , "resources/long/back_10.bmp" , "resources/long/back_11.bmp" ,
		"resources/long/back_12.bmp" , "resources/long/back_13.bmp" , "resources/long/back_14.bmp" ,
		"resources/long/back_15.bmp" , "resources/long/back_16.bmp" , "resources/long/back_17.bmp" ,
		"resources/long/back_18.bmp" , "resources/long/back_19.bmp" , "resources/long/back_20.bmp" ,
		"resources/long/back_21.bmp" , "resources/long/back_22.bmp" , "resources/long/back_23.bmp" ,
		"resources/long/back_24.bmp" , "resources/long/back_25.bmp" , "resources/long/back_26.bmp" ,
		"resources/long/back_27.bmp" , "resources/long/back_28.bmp" , "resources/long/back_29.bmp" ,
		"resources/long/back_30.bmp" , "resources/long/back_31.bmp" , "resources/long/back_32.bmp" ,
		"resources/long/back_33.bmp" , "resources/long/back_34.bmp" , "resources/long/back_35.bmp" ,
			}, RGB(255, 255, 255));

		monster death2(2);
		cat_one_friend_death.push_back(death2);
		cat_one_friend_death[cat_one_friend_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}

	////3
	if (point.x >= 780 && point.x <= 924 && point.y >= 680 && point.y <= 789 && money_30 >= base_3.get_price() && (cat_3_cool.GetFrameIndexOfBitmap() == 24 || debug_mode == 1) && getStage() >= 3) {
		money_30 = money_30 - base_3.get_price();
		money = money - (base_3.get_price() * 30);
		if (debug_mode == 0) {
			character_call_cat_3.SetFrameIndexOfBitmap(2);
			cat_3_cool.SetFrameIndexOfBitmap(0);
			cat_3_cool.SetAnimation(250, 0);
		}
		cat_one_friend_if_death.push_back(false);

		monster temp3(3);
		cat_one_friend.push_back(temp3);
		cat_one_friend[cat_one_friend.size() - 1].LoadBitmapByString({
		"resources/ax/walk_1.bmp" , "resources/ax/walk_2.bmp" , "resources/ax/walk_3.bmp" , "resources/ax/walk_2.bmp"        // 載入貓咪2走路動畫
			}, RGB(237, 28, 36));
		cat_one_friend[cat_one_friend.size() - 1].SetTopLeft(1350, 345);
		cat_one_friend[cat_one_friend.size() - 1].SetAnimation(125, 0);

		cat_one_friend[cat_one_friend.size() - 1].attack.LoadBitmapByString({
		"resources/ax/attack_1.bmp" , "resources/ax/attack_2.bmp" , "resources/ax/attack_1.bmp" ,
		"resources/ax/attack_3.bmp" , "resources/ax/attack_4.bmp" , "resources/ax/attack_4.bmp" ,
		"resources/ax/attack_4.bmp" , "resources/ax/attack_4.bmp" , "resources/ax/walk_2.bmp" ,
		"resources/ax/walk_2.bmp" , "resources/ax/walk_2.bmp" , "resources/ax/walk_2.bmp"        // 載入貓咪3攻擊動畫
			}, RGB(237, 28, 36));

		cat_one_friend[cat_one_friend.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1.bmp" , "resources/bump_2.bmp" , "resources/bump_3.bmp" ,
		"resources/bump_4.bmp" , "resources/bump_5.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入貓咪3攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster back3(3);
		cat_one_friend_back.push_back(back3);
		cat_one_friend_back[cat_one_friend_back.size() - 1].LoadBitmapByString({
		"resources/ax/back_0.bmp" , "resources/ax/back_1.bmp" , "resources/ax/back_2.bmp" ,
		"resources/ax/back_3.bmp" , "resources/ax/back_4.bmp" , "resources/ax/back_5.bmp" ,
		"resources/ax/back_6.bmp" , "resources/ax/back_7.bmp" , "resources/ax/back_8.bmp" ,
		"resources/ax/back_9.bmp" , "resources/ax/back_10.bmp" , "resources/ax/back_11.bmp" ,
		"resources/ax/back_12.bmp" , "resources/ax/back_13.bmp" , "resources/ax/back_14.bmp" ,
		"resources/ax/back_15.bmp" , "resources/ax/back_16.bmp" , "resources/ax/back_17.bmp" ,
		"resources/ax/back_18.bmp" , "resources/ax/back_19.bmp" , "resources/ax/back_20.bmp" ,
		"resources/ax/back_21.bmp" , "resources/ax/back_22.bmp" , "resources/ax/back_23.bmp" ,
		"resources/ax/back_24.bmp" , "resources/ax/back_25.bmp" , "resources/ax/back_26.bmp" ,
		"resources/ax/back_27.bmp" , "resources/ax/back_28.bmp" , "resources/ax/back_29.bmp" ,
		"resources/ax/back_30.bmp" , "resources/ax/back_31.bmp" , "resources/ax/back_32.bmp" ,
		"resources/ax/back_33.bmp" , "resources/ax/back_34.bmp" , "resources/ax/back_35.bmp" ,
			}, RGB(237, 28, 36));

		monster death2(2);
		cat_one_friend_death.push_back(death2);
		cat_one_friend_death[cat_one_friend_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}

	////4
	if (point.x >= 935 && point.x <= 1079 && point.y >= 680 && point.y <= 789 && money_30 >= base_4.get_price() && (cat_4_cool.GetFrameIndexOfBitmap() == 24 || debug_mode == 1) && getStage() >= 4) {
		money_30 = money_30 - base_4.get_price();
		money = money - (base_4.get_price() * 30);
		if (debug_mode == 0) {
			character_call_cat_4.SetFrameIndexOfBitmap(2);
			cat_4_cool.SetFrameIndexOfBitmap(0);
			cat_4_cool.SetAnimation(250, 0);
		}
		cat_one_friend_if_death.push_back(false);

		monster temp4(4);
		cat_one_friend.push_back(temp4);
		cat_one_friend[cat_one_friend.size() - 1].LoadBitmapByString({
		"resources/ba/walk_1.bmp" , "resources/ba/walk_2.bmp" , "resources/ba/walk_3.bmp" , "resources/ba/walk_2.bmp"        // 載入貓咪走路動畫
			}, RGB(237, 28, 36));
		cat_one_friend[cat_one_friend.size() - 1].SetTopLeft(1350, 200);
		cat_one_friend[cat_one_friend.size() - 1].SetAnimation(125, 0);

		cat_one_friend[cat_one_friend.size() - 1].attack.LoadBitmapByString({
		"resources/ba/attack_1.bmp" , "resources/ba/attack_2.bmp" , "resources/ba/attack_3.bmp" ,
		"resources/ba/attack_3.bmp" , "resources/ba/attack_4.bmp" , "resources/ba/attack_7.bmp" ,
		"resources/ba/attack_8.bmp" , "resources/ba/attack_9.bmp" , "resources/ba/attack_10.bmp" ,
		"resources/ba/walk_2.bmp" , "resources/ba/walk_2.bmp" , "resources/ba/walk_2.bmp"          // 載入貓咪攻擊動畫
			}, RGB(237, 28, 36));

		cat_one_friend[cat_one_friend.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1.bmp" , "resources/bump_2.bmp" , "resources/bump_3.bmp" ,
		"resources/bump_4.bmp" , "resources/bump_5.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入貓咪攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster back2(2);
		cat_one_friend_back.push_back(back2);
		cat_one_friend_back[cat_one_friend_back.size() - 1].LoadBitmapByString({
		"resources/ba/back_0.bmp" , "resources/ba/back_1.bmp" , "resources/ba/back_2.bmp" ,
		"resources/ba/back_3.bmp" , "resources/ba/back_4.bmp" , "resources/ba/back_5.bmp" ,
		"resources/ba/back_6.bmp" , "resources/ba/back_7.bmp" , "resources/ba/back_8.bmp" ,
		"resources/ba/back_9.bmp" , "resources/ba/back_10.bmp" , "resources/ba/back_11.bmp" ,
		"resources/ba/back_12.bmp" , "resources/ba/back_13.bmp" , "resources/ba/back_14.bmp" ,
		"resources/ba/back_15.bmp" , "resources/ba/back_16.bmp" , "resources/ba/back_17.bmp" ,
		"resources/ba/back_18.bmp" , "resources/ba/back_19.bmp" , "resources/ba/back_20.bmp" ,
		"resources/ba/back_21.bmp" , "resources/ba/back_22.bmp" , "resources/ba/back_23.bmp" ,
		"resources/ba/back_24.bmp" , "resources/ba/back_25.bmp" , "resources/ba/back_26.bmp" ,
		"resources/ba/back_27.bmp" , "resources/ba/back_28.bmp" , "resources/ba/back_29.bmp" ,
		"resources/ba/back_30.bmp" , "resources/ba/back_31.bmp" , "resources/ba/back_32.bmp" ,
		"resources/ba/back_33.bmp" , "resources/ba/back_34.bmp" , "resources/ba/back_35.bmp" ,
			}, RGB(237, 28, 36));

		monster death2(2);
		cat_one_friend_death.push_back(death2);
		cat_one_friend_death[cat_one_friend_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}

	////5
	if (point.x >= 1090 && point.x <= 1234 && point.y >= 680 && point.y <= 789 && money_30 >= base_5.get_price() && (cat_5_cool.GetFrameIndexOfBitmap() == 24 || debug_mode == 1) && getStage() == 5) {
		money_30 = money_30 - base_5.get_price();
		money = money - (base_5.get_price() * 30);
		if (debug_mode == 0) {
			character_call_cat_5.SetFrameIndexOfBitmap(2);
			cat_5_cool.SetFrameIndexOfBitmap(0);
			cat_5_cool.SetAnimation(250, 0);
		}
		cat_one_friend_if_death.push_back(false);

		monster temp5(5);
		cat_one_friend.push_back(temp5);
		cat_one_friend[cat_one_friend.size() - 1].LoadBitmapByString({
		"resources/bi/walk_1.bmp" , "resources/bi/walk_2.bmp" , "resources/bi/walk_3.bmp" , "resources/bi/walk_2.bmp"        // 載入貓咪走路動畫
			}, RGB(237, 28, 36));
		cat_one_friend[cat_one_friend.size() - 1].SetTopLeft(1340, 245);
		cat_one_friend[cat_one_friend.size() - 1].SetAnimation(125, 0);

		cat_one_friend[cat_one_friend.size() - 1].attack.LoadBitmapByString({
		"resources/bi/attack_1.bmp" , "resources/bi/attack_2.bmp" , "resources/bi/attack_3.bmp" ,
		"resources/bi/attack_4.bmp" , "resources/bi/attack_5.bmp" , "resources/bi/attack_6.bmp" ,
		"resources/bi/attack_13.bmp" , "resources/bi/attack_14.bmp" ,"resources/bi/attack_15.bmp" ,
		"resources/bi/attack_16.bmp" , "resources/bi/walk_2.bmp" , "resources/bi/walk_2.bmp"           // 載入貓咪攻擊動畫
			}, RGB(237, 28, 36));

		cat_one_friend[cat_one_friend.size() - 1].bump.LoadBitmapByString({
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_1.bmp" , "resources/bump_2.bmp" , "resources/bump_3.bmp" ,
		"resources/bump_4.bmp" , "resources/bump_5.bmp" , "resources/bump_0.bmp" ,
		"resources/bump_0.bmp" , "resources/bump_0.bmp" , "resources/bump_0.bmp"        // 載入貓咪攻擊爆炸動畫
			}, RGB(255, 255, 255));

		monster back2(2);
		cat_one_friend_back.push_back(back2);
		cat_one_friend_back[cat_one_friend_back.size() - 1].LoadBitmapByString({
		"resources/bi/back_0.bmp" , "resources/bi/back_1.bmp" , "resources/bi/back_2.bmp" ,
		"resources/bi/back_3.bmp" , "resources/bi/back_4.bmp" , "resources/bi/back_5.bmp" ,
		"resources/bi/back_6.bmp" , "resources/bi/back_7.bmp" , "resources/bi/back_8.bmp" ,
		"resources/bi/back_9.bmp" , "resources/bi/back_10.bmp" , "resources/bi/back_11.bmp" ,
		"resources/bi/back_12.bmp" , "resources/bi/back_13.bmp" , "resources/bi/back_14.bmp" ,
		"resources/bi/back_15.bmp" , "resources/bi/back_16.bmp" , "resources/bi/back_17.bmp" ,
		"resources/bi/back_18.bmp" , "resources/bi/back_19.bmp" , "resources/bi/back_20.bmp" ,
		"resources/bi/back_21.bmp" , "resources/bi/back_22.bmp" , "resources/bi/back_23.bmp" ,
		"resources/bi/back_24.bmp" , "resources/bi/back_25.bmp" , "resources/bi/back_26.bmp" ,
		"resources/bi/back_27.bmp" , "resources/bi/back_28.bmp" , "resources/bi/back_29.bmp" ,
		"resources/bi/back_30.bmp" , "resources/bi/back_31.bmp" , "resources/bi/back_32.bmp" ,
		"resources/bi/back_33.bmp" , "resources/bi/back_34.bmp" , "resources/bi/back_35.bmp" ,
			}, RGB(237, 28, 36));

		monster death2(2);
		cat_one_friend_death.push_back(death2);
		cat_one_friend_death[cat_one_friend_death.size() - 1].LoadBitmapByString({
		"resources/death_1.bmp" , "resources/death_2.bmp" , "resources/death_3.bmp" ,
		"resources/death_4.bmp" , "resources/death_5.bmp" , "resources/death_6.bmp" ,
		"resources/death_7.bmp" , "resources/death_8.bmp" , "resources/death_9.bmp" ,
		"resources/death_10.bmp" , "resources/death_11.bmp" , "resources/death_12.bmp" ,
		"resources/death_13.bmp" , "resources/death_14.bmp" , "resources/death_15.bmp" ,
		"resources/death_16.bmp" , "resources/death_17.bmp" , "resources/death_18.bmp" ,
		"resources/death_19.bmp" , "resources/death_20.bmp" , "resources/death_21.bmp" ,
		"resources/death_22.bmp" , "resources/death_23.bmp" , "resources/death_24.bmp" ,
		"resources/death_25.bmp" , "resources/death_26.bmp" , "resources/death_27.bmp" ,
		"resources/death_28.bmp" , "resources/death_29.bmp" , "resources/death_30.bmp" ,
		"resources/death_31.bmp" , "resources/death_32.bmp" , "resources/death_33.bmp" ,
		"resources/death_34.bmp" , "resources/death_35.bmp" , "resources/death_36.bmp" ,
		"resources/death_37.bmp" , "resources/death_38.bmp" , "resources/death_39.bmp" ,
		"resources/death_40.bmp" , "resources/death_41.bmp" , "resources/death_42.bmp" ,
		"resources/death_43.bmp" , "resources/death_44.bmp" , "resources/death_45.bmp" ,
		"resources/death_46.bmp" , "resources/death_47.bmp" , "resources/death_48.bmp" ,
		"resources/death_49.bmp" , "resources/death_50.bmp" , "resources/death_51.bmp" ,
		"resources/death_52.bmp" , "resources/death_53.bmp" , "resources/death_54.bmp" ,
		"resources/death_55.bmp" , "resources/death_56.bmp" , "resources/death_57.bmp" ,
		"resources/death_58.bmp" , "resources/death_59.bmp" , "resources/death_60.bmp" ,
		"resources/death_61.bmp"
			}, RGB(255, 255, 255));
	}
	////
	if (point.x > 50 && point.x < 292 && point.y > 636 && point.y < 800 && money_30 >= now_Level * 40 && now_Level < 8) {
		
		money_30 -= now_Level * 40;
		max_money_30 += 50  * now_Level;
		money_persecond += 1.5*now_Level;
		money -= (now_Level * 40 * 30);
		Level_shine[now_Level - 1].SetFrameIndexOfBitmap(0);
		now_Level += 1;
		Level_dark.SetFrameIndexOfBitmap(now_Level - 1);
	}
}

void CGameStateRun_3::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun_3::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun_3::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun_3::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun_3::OnShow()
{
	background.ShowBitmap();        // 顯示關卡背景
	money_map.ShowBitmap();
	if (money_30 < now_Level * 40 && now_Level <= 8) {
		Level_dark.ShowBitmap();
	}
	else if (money_30 >= now_Level * 40 && now_Level < 8) {
		Level_shine[now_Level - 1].SetAnimation(100, 0);
		Level_shine[now_Level - 1].ShowBitmap();
	}
	draw_text();
	if (cat_1_cool.GetFrameIndexOfBitmap() > 23 && getStage() >= 1) {        // 顯示招喚貓咪1按鈕與冷卻
		if (money_30 < base_1.get_price()) {
			character_call_cat_1.SetFrameIndexOfBitmap(1);
		}
		character_call_cat_1.ShowBitmap();
		cat_1_cool.SetFrameIndexOfBitmap(24);
	}
	else {
		character_call_cat_1.ShowBitmap();
		cat_1_cool.ShowBitmap();
	}
	////2
	if (cat_2_cool.GetFrameIndexOfBitmap() > 23 && getStage() >= 2) {        // 顯示招喚貓咪2按鈕與冷卻
		if (money_30 < base_2.get_price()) {
			character_call_cat_2.SetFrameIndexOfBitmap(1);
		}
		character_call_cat_2.ShowBitmap();
		cat_2_cool.SetFrameIndexOfBitmap(24);
	}
	else {
		character_call_cat_2.ShowBitmap();
		if (getStage() >= 2) {
			cat_2_cool.ShowBitmap();
		}
	}
	/////3
	if (cat_3_cool.GetFrameIndexOfBitmap() > 23 && getStage() >= 3) {
		if (money_30 < base_3.get_price()) {
			character_call_cat_3.SetFrameIndexOfBitmap(1);
		}
		character_call_cat_3.ShowBitmap();
		cat_3_cool.SetFrameIndexOfBitmap(24);
	}
	else {
		character_call_cat_3.ShowBitmap();
		if (getStage() >= 3) {
			cat_3_cool.ShowBitmap();
		}
	}
	/////4
	if (cat_4_cool.GetFrameIndexOfBitmap() > 23 && getStage() >= 4) {
		if (money_30 < base_4.get_price()) {
			character_call_cat_4.SetFrameIndexOfBitmap(1);
		}
		character_call_cat_4.ShowBitmap();
		cat_4_cool.SetFrameIndexOfBitmap(24);
	}
	else {
		character_call_cat_4.ShowBitmap();
		if (getStage() >= 4) {
			cat_4_cool.ShowBitmap();
		}
	}
	/////5
	if (cat_5_cool.GetFrameIndexOfBitmap() > 23 && getStage() >= 5) {
		if (money_30 < base_5.get_price()) {
			character_call_cat_5.SetFrameIndexOfBitmap(1);
		}
		character_call_cat_5.ShowBitmap();
		cat_5_cool.SetFrameIndexOfBitmap(24);
	}
	else {
		character_call_cat_5.ShowBitmap();
		if (getStage() >= 5) {
			cat_5_cool.ShowBitmap();
		}
	}
	/////

	character_tower_1.ShowBitmap();        // 顯示己方防禦塔
	character_tower_2.ShowBitmap();        // 顯示敵方防禦塔

	///////////////////////////////////////////
	// 顯示敵對生物及貓咪所有動畫、動畫切換
	///////////////////////////////////////////
	for (int d = 0; d < enemy_one_v.size(); d++) {
		int t = 0;
		for (int i = 0; i < cat_one_friend.size(); i++) {
			if (enemy_one_v[d].GetLeft() + 50 + enemy_one_v[d].GetWidth() < cat_one_friend[i].GetLeft() || cat_one_friend_if_death[i]) {
				t += 1;
			}
		}
		if ((t == cat_one_friend.size() || cat_one_friend.size() == 0) && enemy_one_v[d].GetLeft() + 50 + enemy_one_v[d].GetWidth() < character_tower_1.GetLeft() && enemy_one_v[d].get_type() != 2) {
			if (enemy_one_v[d].get_type() == 1) {
				enemy_one_v[d].SetTopLeft(enemy_one_v[d].attack.GetLeft(), enemy_one_v[d].attack.GetTop());
				enemy_one_v[d].type = 0;
			}
			if (!(enemy_one_v_if_death[d])) {
				enemy_one_v[d].SetAnimation(250, 0);
				enemy_one_v[d].ShowBitmap();
			}
		}
		else {
			if (enemy_one_v[d].get_type() != 2 && !(enemy_one_v_if_death[d])) {
				if (enemy_one_v[d].get_type() == 0) {
					enemy_one_v[d].attack.SetTopLeft(enemy_one_v[d].GetLeft(), enemy_one_v[d].GetTop());
					enemy_one_v[d].type = 1;
				}
				enemy_one_v[d].attack.SetAnimation(100, 0);
				enemy_one_v[d].bump.SetTopLeft(enemy_one_v[d].GetLeft() + 100, enemy_one_v[d].GetTop() - 25);
				enemy_one_v[d].bump.SetAnimation(100, 0);
				enemy_one_v[d].bump.ShowBitmap();
				enemy_one_v[d].attack.SetAnimation(100, 0);
				enemy_one_v[d].attack.ShowBitmap();
				enemy_one_v[d].whether_attack = true;
		

				if (enemy_one_v[d].attack.GetFrameIndexOfBitmap() == 1) {
					enemy_one_v[d].if_attack = 0;
				}

				int now_position_cat;
				int now_position = 1900;

				for (int j = 0; j < cat_one_friend.size(); j++) {
					if (cat_one_friend[j].GetLeft() < now_position) {
						now_position = enemy_one_v[j].GetLeft() + enemy_one_v[j].GetWidth();
						now_position_cat = j;
					}
				}
				if (enemy_one_v[d].attack.GetFrameIndexOfBitmap() == 4  && enemy_one_v[d].get_if_attack() == 0) { //設定攻擊動畫扣血
					if (cat_one_friend.size() > 0) {
						if (enemy_one_v[now_position_cat].GetLeft() > 1400) {
							friend_tower -= enemy_one_v[d].get_power();
							enemy_one_v[d].if_attack = 1;
							if (friend_tower <= 0) {
								GotoGameState(GAME_STATE_RUN);
							}
						}
						else {
							cat_one_friend[now_position_cat].heart -= enemy_one_v[now_position_cat].power;
							enemy_one_v[d].if_attack = 1;
							if (cat_one_friend[now_position_cat].heart <= 0) {
								enemy_one_v[d].attack.SetFrameIndexOfBitmap(0);
								enemy_one_v[d].bump.SetFrameIndexOfBitmap(0);
								cat_one_friend_if_death[now_position_cat] = true;
								cat_one_friend_back[now_position_cat].SetTopLeft(cat_one_friend[now_position_cat].GetLeft(), cat_one_friend[now_position_cat].GetTop() - 50);
								cat_one_friend_death[now_position_cat].SetTopLeft(cat_one_friend[now_position_cat].GetLeft() + 136, 0);
								cat_one_friend_back[now_position_cat].SetAnimation(20, 0);
								cat_one_friend.erase(cat_one_friend.begin() + now_position_cat);
							}
							else if (cat_one_friend[now_position_cat].heart <= 15 && cat_one_friend[now_position_cat].get_back_time() == 0) {
								cat_one_friend[now_position_cat].back_time = 1;
								cat_one_friend[now_position_cat].type = 2;
								enemy_one_v[d].attack.SetFrameIndexOfBitmap(0);
								enemy_one_v[d].bump.SetFrameIndexOfBitmap(0);
								cat_one_friend_back[now_position_cat].SetTopLeft(cat_one_friend[now_position_cat].GetLeft(), cat_one_friend[now_position_cat].GetTop() - 50);
								cat_one_friend[now_position_cat].SetTopLeft(cat_one_friend[now_position_cat].GetLeft() + 136, cat_one_friend[now_position_cat].GetTop());
								cat_one_friend[now_position_cat].attack.SetTopLeft(cat_one_friend[now_position_cat].GetLeft(), cat_one_friend[now_position_cat].GetTop());
								cat_one_friend[now_position_cat].attack.SetFrameIndexOfBitmap(0);
								cat_one_friend[now_position_cat].bump.SetFrameIndexOfBitmap(0);
								cat_one_friend_back[now_position_cat].SetAnimation(20, 0);
							}
						}
					}
					else {
						friend_tower -= enemy_one_v[d].get_power();
						enemy_one_v[d].if_attack = 1;
						if (friend_tower <= 0) {
							GotoGameState(GAME_STATE_RUN);
						}
					}
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < cat_one_friend_back.size(); i++) {
		if (!(cat_one_friend_if_death[i])) {
			if (cat_one_friend_back[i].IsAnimation() && cat_one_friend[i].get_type() == 2) {
				cat_one_friend_back[i].ShowBitmap();
			}
			if (cat_one_friend_back[i].GetFrameIndexOfBitmap() > 33 && cat_one_friend[i].get_type() == 2) {
				cat_one_friend_back[i].SetFrameIndexOfBitmap(0);
				cat_one_friend[i].type = 1;
			}
		}
	}
	for (int i = 0; i < cat_one_friend_back.size(); i++) {
		if (cat_one_friend_back[i].IsAnimation() && cat_one_friend_if_death[i]) {
			cat_one_friend_back[i].ShowBitmap();
		}
		if (cat_one_friend_back[i].GetFrameIndexOfBitmap() > 33 && cat_one_friend_if_death[i]) {
			cat_one_friend_death[i].SetAnimation(15, 0);
			cat_one_friend_back.erase(cat_one_friend_back.begin() + i);
			cat_one_friend_if_death.erase(cat_one_friend_if_death.begin() + i);
			i -= 1;
		}
	}
	for (int i = 0; i < cat_one_friend_death.size(); i++) {
		if (cat_one_friend_death[i].IsAnimation()) {
			cat_one_friend_death[i].ShowBitmap();
		}
		if (cat_one_friend_death[i].GetFrameIndexOfBitmap() > 59) {
			cat_one_friend_death.erase(cat_one_friend_death.begin() + i);
			i -= 1;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////

	for (int i = 0; i < cat_one_friend.size(); i++) {
		int t = 0;
		for (int d = 0; d < enemy_one_v.size(); d++) {
			if (enemy_one_v[d].GetLeft() + 50 + enemy_one_v[d].GetWidth() < cat_one_friend[i].GetLeft() || enemy_one_v_if_death[d]) {
				t += 1;
			}
		}
		if ((t == enemy_one_v.size() || enemy_one_v.size() == 0) && cat_one_friend[i].GetLeft() > character_tower_2.GetLeft() + 50 + character_tower_2.GetWidth() && cat_one_friend[i].get_type() != 2) {
			if (cat_one_friend[i].get_type() == 1) {
				cat_one_friend[i].SetTopLeft(cat_one_friend[i].attack.GetLeft(), cat_one_friend[i].attack.GetTop());
				cat_one_friend[i].type = 0;
			}
			cat_one_friend[i].SetAnimation(125, 0);
			cat_one_friend[i].ShowBitmap();
		}
		else {
			if (cat_one_friend[i].get_type() != 2) {
				if (true) {
					cat_one_friend[i].attack.SetTopLeft(cat_one_friend[i].GetLeft(), cat_one_friend[i].GetTop());
					cat_one_friend[i].type = 1;
				}
				cat_one_friend[i].bump.SetTopLeft(cat_one_friend[i].GetLeft() - 150, cat_one_friend[i].GetTop() - 25);
				cat_one_friend[i].attack.SetAnimation(100, 0);
				cat_one_friend[i].bump.SetAnimation(100, 0);
				cat_one_friend[i].attack.ShowBitmap();
				cat_one_friend[i].bump.ShowBitmap();
				if (cat_one_friend[i].attack.GetFrameIndexOfBitmap() == 1) {
					cat_one_friend[i].if_attack = 0;
				}
				int now_position_enemy;
				int now_position = 0;

				for (int j = 0; j < enemy_one_v.size(); j++) {
					if (enemy_one_v[j].GetLeft() + enemy_one_v[j].GetWidth() > now_position) {
						now_position = enemy_one_v[j].GetLeft() + enemy_one_v[j].GetWidth();
						now_position_enemy = j;
					}
				}
				if (cat_one_friend[i].attack.GetFrameIndexOfBitmap() == 4 && cat_one_friend[i].get_type() == 1 && cat_one_friend[i].get_if_attack() == 0) { //設定攻擊動畫扣血	
					if (enemy_one_v.size() > 0) {
						if (enemy_one_v[now_position_enemy].GetLeft() < 100) {//如果都在塔後
							enemy_tower -= cat_one_friend[i].get_power();
							cat_one_friend[i].if_attack = 1;
							for (int j = 0; j < enemy_one_v.size(); j++) {
								if (enemy_one_v[j].GetLeft() + enemy_one_v[j].GetWidth() > cat_one_friend[i].GetLeft() - cat_one_friend[i].get_attack_range() && cat_one_friend[i].get_single_attack() == 1) {
									enemy_one_v[j].heart -= cat_one_friend[i].get_power();
								}
							}
							if (enemy_tower <= 0) {
								GotoGameState(GAME_STATE_RUN);
							}
						}
						else {
							if (cat_one_friend[i].get_single_attack() == 1 && cat_one_friend[i].get_if_attack() == 0) {
								enemy_one_v[now_position_enemy].heart -= cat_one_friend[i].power;
								cat_one_friend[i].if_attack = 1;
								if (enemy_one_v[now_position_enemy].heart <= 0 && !(enemy_one_v_if_death[now_position_enemy])) {
									cat_one_friend[i].attack.SetFrameIndexOfBitmap(0);
									cat_one_friend[i].bump.SetFrameIndexOfBitmap(0);
									enemy_one_v_if_death[now_position_enemy] = true;
									enemy_one_v_back[now_position_enemy].SetTopLeft(enemy_one_v[now_position_enemy].GetLeft() - 136, enemy_one_v[now_position_enemy].GetTop() - 50);
									enemy_one_v_death[now_position_enemy].SetTopLeft(enemy_one_v[now_position_enemy].GetLeft() - 136, 0);
									enemy_one_v_back[now_position_enemy].SetAnimation(20, 0);
									//enemy_one_v.erase(enemy_one_v.begin() + now_position_enemy);
								}
								else if (enemy_one_v[now_position_enemy].heart <= 15 && enemy_one_v[now_position_enemy].get_back_time() == 0) {
									enemy_one_v[now_position_enemy].back_time = 1;
									enemy_one_v[now_position_enemy].type = 2;
									cat_one_friend[i].attack.SetFrameIndexOfBitmap(0);
									cat_one_friend[i].bump.SetFrameIndexOfBitmap(0);
									enemy_one_v[now_position_enemy].SetTopLeft(enemy_one_v[now_position_enemy].GetLeft() - 136, enemy_one_v[now_position_enemy].GetTop());
									enemy_one_v[now_position_enemy].attack.SetTopLeft(enemy_one_v[now_position_enemy].GetLeft(), enemy_one_v[now_position_enemy].GetTop());
									enemy_one_v_back[now_position_enemy].SetTopLeft(enemy_one_v[now_position_enemy].GetLeft(), enemy_one_v[now_position_enemy].GetTop() - 50);
									enemy_one_v[now_position_enemy].attack.SetFrameIndexOfBitmap(0);
									enemy_one_v[now_position_enemy].bump.SetFrameIndexOfBitmap(0);
									enemy_one_v_back[now_position_enemy].SetAnimation(20, 0);
								}
							}
							else if (cat_one_friend[i].get_single_attack() == 0) {
								cat_one_friend[i].if_attack = 1;
								for (int j = 0; j < enemy_one_v.size(); j++) {
									if ((enemy_one_v[j].GetLeft() + enemy_one_v[j].GetWidth() > cat_one_friend[i].GetLeft() - cat_one_friend[i].get_attack_range()) && !(enemy_one_v_if_death[j])) {
										enemy_one_v[j].heart -= cat_one_friend[i].get_power();
									}

									if (enemy_one_v[j].heart <= 0 && !(enemy_one_v_if_death[j])) {

										cat_one_friend[i].attack.SetFrameIndexOfBitmap(0);
										cat_one_friend[i].bump.SetFrameIndexOfBitmap(0);
										enemy_one_v_if_death[j] = true;
										enemy_one_v_back[j].SetTopLeft(enemy_one_v[j].GetLeft() - 136, enemy_one_v[j].GetTop() - 50);
										enemy_one_v_death[j].SetTopLeft(enemy_one_v[j].GetLeft() - 136, 0);
										enemy_one_v[j].SetTopLeft(enemy_one_v[j].GetLeft() - 136, enemy_one_v[j].GetTop());
										enemy_one_v[j].attack.SetTopLeft(enemy_one_v[j].GetLeft(), enemy_one_v[j].GetTop());
										enemy_one_v[j].bump.SetTopLeft(enemy_one_v[j].GetLeft(), enemy_one_v[j].GetTop());
										enemy_one_v_back[j].SetAnimation(20, 0);
										enemy_one_v_back[j].ShowBitmap();
									}
									else if (enemy_one_v[j].heart <= 15 && enemy_one_v[j].get_back_time() == 0) {

										enemy_one_v[j].back_time = 1;
										enemy_one_v[j].type = 2;
										cat_one_friend[i].attack.SetFrameIndexOfBitmap(0);
										cat_one_friend[i].bump.SetFrameIndexOfBitmap(0);
										enemy_one_v[j].SetTopLeft(enemy_one_v[j].GetLeft() - 136, enemy_one_v[j].GetTop());
										enemy_one_v[j].attack.SetTopLeft(enemy_one_v[j].GetLeft(), enemy_one_v[j].GetTop());
										enemy_one_v_back[j].SetTopLeft(enemy_one_v[j].GetLeft(), enemy_one_v[j].GetTop() - 50);
										enemy_one_v[j].attack.SetFrameIndexOfBitmap(0);
										enemy_one_v[j].bump.SetFrameIndexOfBitmap(0);
										enemy_one_v_back[j].SetAnimation(20, 0);
									}
								}
							}
						}
					}
					else {
						enemy_tower -= cat_one_friend[i].get_power();
						cat_one_friend[i].if_attack = 1;
						if (enemy_tower <= 0) {
							GotoGameState(GAME_STATE_RUN);
						}
					}
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////
	for (int d = 0; d < enemy_one_v_back.size(); d++) {
		if (!(enemy_one_v_if_death[d])) {
			if (enemy_one_v_back[d].IsAnimation() && enemy_one_v[d].get_type() == 2) {
				enemy_one_v_back[d].ShowBitmap();
			}
			if (enemy_one_v_back[d].GetFrameIndexOfBitmap() > 33 && enemy_one_v[d].get_type() == 2) {
				enemy_one_v_back[d].SetFrameIndexOfBitmap(0);
				enemy_one_v[d].type = 1;
			}
		}
	}
	for (int d = 0; d < enemy_one_v_back.size(); d++) {
		if (enemy_one_v_back[d].IsAnimation() && enemy_one_v_if_death[d] && enemy_one_v_back[d].GetFrameIndexOfBitmap() != 34) {
			enemy_one_v_back[d].ShowBitmap();
		}
		if (enemy_one_v_back[d].GetFrameIndexOfBitmap() > 33 && enemy_one_v_if_death[d]) {
			enemy_one_v_death[d].SetAnimation(15, 0);
			enemy_one_v_back[d].SetFrameIndexOfBitmap(34);
		}
	}
	for (int d = 0; d < enemy_one_v_death.size(); d++) {
		if (enemy_one_v_death[d].IsAnimation()) {
			enemy_one_v_death[d].ShowBitmap();
		}
		if (enemy_one_v_death[d].GetFrameIndexOfBitmap() > 59) {
			enemy_one_v_back.erase(enemy_one_v_back.begin() + d);
			enemy_one_v_if_death.erase(enemy_one_v_if_death.begin() + d);
			enemy_one_v.erase(enemy_one_v.begin() + d);
			enemy_one_v_death.erase(enemy_one_v_death.begin() + d);
			d -= 1;
		}
	}
	for (int d = 0; d < enemy_one_v.size(); d++) {
		if (enemy_one_v[d].get_whether_attack()) {
			enemy_one_v[d].bump.ShowBitmap();
			enemy_one_v[d].whether_attack = false;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////
}

void CGameStateRun_3::draw_text() {
	int Px = 1385;
	CDC *pDC = CDDraw::GetBackCDC();
	//CFont* fp;
	s = std::to_string(money_30);
	s2 = std::to_string(max_money_30);
	int move = 0;
	std::string  print = s + "/" + s2;
	CTextDraw::ChangeFontLog(pDC, 30, "Arial Black", RGB(255, 200, 0), 900);

	if (debug_mode == 1) {

		CTextDraw::ChangeFontLog(pDC, 30, "Arial Black", RGB(255, 0, 0), 900);
		a = std::to_string(getStage());
		CTextDraw::Print(pDC, 1200, 105, "stage:" + a);
		a2 = std::to_string(cat_one_friend.size());
		CTextDraw::Print(pDC, 700, 105, "cat_count:" + a2);
		a2 = std::to_string(enemy_one_v.size());
		CTextDraw::Print(pDC, 200, 105, "enemy_count:" + a2);
		/*
		a2 = std::to_string(monster(1).get_heart());
		CTextDraw::Print(pDC, 500, 150, "cat_lifevalue:" + a2);		
		*/
	}
	
	if (money_30 > 9) {
		Px -= 25;
	}
	if (money_30 > 99) {
		Px -= 25;
	}
	if (max_money_30 > 999 ) {
		Px -= 25;
		if (money_30 > 999) {
			Px -= 25;
		}
	}
	
	CTextDraw::Print(pDC, Px, 3, print);
	CTextDraw::ChangeFontLog(pDC, 20, "Arial Black", RGB(0, 0, 0), 900);

	if (getStage() == 1) {
		show_friend_tower = std::to_string(friend_tower);
		CTextDraw::Print(pDC, 1290, 175, (show_friend_tower + "/1000"));
		show_enemy_tower = std::to_string(enemy_tower);
		CTextDraw::Print(pDC, 255, 175, (show_enemy_tower + "/500"));
	}
	if (getStage() == 2) {
		show_friend_tower = std::to_string(friend_tower);
		CTextDraw::Print(pDC, 1290, 175, (show_friend_tower + "/1000"));
		show_enemy_tower = std::to_string(enemy_tower);
		CTextDraw::Print(pDC, 255, 175, (show_enemy_tower + "/800"));
	}
	if (getStage() == 3) {
		show_friend_tower = std::to_string(friend_tower);
		CTextDraw::Print(pDC, 1290, 175, (show_friend_tower + "/1000"));
		show_enemy_tower = std::to_string(enemy_tower);
		CTextDraw::Print(pDC, 257, 175, (show_enemy_tower + "/1000"));
	}
	if (getStage() == 4) {
		show_friend_tower = std::to_string(friend_tower);
		CTextDraw::Print(pDC, 1290, 175, (show_friend_tower + "/1000"));
		show_enemy_tower = std::to_string(enemy_tower);
		CTextDraw::Print(pDC, 265, 175, (show_enemy_tower + "/1500"));
	}
	if (getStage() == 5) {
		show_friend_tower = std::to_string(friend_tower);
		CTextDraw::Print(pDC, 1290, 175, (show_friend_tower + "/1500"));
		show_enemy_tower = std::to_string(enemy_tower);
		CTextDraw::Print(pDC, 265, 175, (show_enemy_tower + "/1500"));
	}

	CDDraw::ReleaseBackCDC();
}