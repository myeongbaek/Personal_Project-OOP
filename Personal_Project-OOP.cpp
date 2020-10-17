#include<stdio.h>
#include<bangtal>
using namespace bangtal;

int main() {
	int game = 3, enter = 0, begin = 0;


	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	auto scene0 = Scene::create("배경0", "Images/마지막배경.png");
	auto scene1 = Scene::create("배경1", "Images/배경.png");
	auto scene2 = Scene::create("배경2", "Images/입다문남자배경.png");
	auto scene3 = Scene::create("배경3", "Images/시작배경.png");

	auto startButton = Object::create("Images/start.png", scene3, 590, 70);
	auto endButton = Object::create("Images/end.png", scene3, 590, 20);

	//game0
	int arm_x = -1000, arm_y = 200;
	int b_x = 200, b_y = 540;
	int velocity = 30;

	auto coin0 = Object::create("Images/500원.png", scene0, 1050, 200, 1); coin0->setScale(0.4f);
	auto arm = Object::create("Images/긴팔.png", scene0, arm_x, arm_y, 1);
	auto fire_frame = Object::create("Images/화염.png", scene0, 0, 0, 0);
	auto fire = Object::create("Images/피살기.png", scene0, 1100, 510, 0); fire->setScale(0.7f);
	auto button2 = Object::create("Images/버튼.png", scene0, b_x, b_y, 0); button2->setScale(0.5f);
	auto dancing_cat = Object::create("Images/귀여운고양이1.png", scene0, 1000, 350, 1); dancing_cat->setScale(0.3f);

	auto count0 = 0;
	auto timer0 = Timer::create(0.1f);
	timer0->setOnTimerCallback([&](TimerPtr t)->bool {
		arm_x -= 10;
		arm->locate(scene0, arm_x, arm_y);

		if (count0 < 72 && count0 > 70) fire->show();
		if (count0 < 22 && count0 > 20) {
			b_x = 1050, b_y = 60;
			button2->locate(scene0, b_x, b_y);
			velocity -= 10;
		}

		switch (count0 % 3) {
		case 1: dancing_cat->setImage("Images/귀여운고양이1.png"); break;
		case 2: dancing_cat->setImage("Images/귀여운고양이2.png"); break;
		case 0: dancing_cat->setImage("Images/귀여운고양이3.png"); break;
		}

		if (arm_x < -1200) {
			showMessage("저런!! 실패했군요!!");
			button2->hide();
			startButton->setImage("Images/restart.png");
			startButton->show();
			endButton->show();//실패시
			begin = 0;
		}
		else {
			t->set(0.1f);
			t->start();
		}

		count0++;

		return true;
		});

	fire->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		fire->hide();
		fire_frame->show();
		velocity += 30;
		return true;
		});

	button2->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (begin) {
			if (arm_x <= -100) {
				arm_x += velocity;
				arm->locate(scene0, arm_x, arm_y);
			}
			else {
				showMessage("모두 성공!! 추천 부탁합니다!!");// 성공시
				timer0->stop();
				button2->hide();
				startButton->setImage("Images/start.png");
				endButton->show();
			}
		}
		return true;
		});


	//game1
	int cat_x = 0, cat_y = 70;
	int hand_g_x = 900, hand_g_y = 600;
	int button_x = 200, button_y = 540;

	auto coin = Object::create("Images/500원.png", scene1, 800, 100, 1);
	auto hand_grap = Object::create("Images/집는손.png", scene1, hand_g_x, hand_g_y);
	auto cat = Object::create("Images/귀여운고양이1.png", scene1, cat_x, cat_y, 1);
	auto button1 = Object::create("Images/버튼.png", scene1, button_x, button_y, 0);

	hand_grap->setScale(0.3f);
	button1->setScale(0.5f);
	coin->setScale(0.5f);
	cat->setScale(0.7f);

	auto count1 = 0;
	auto timer1 = Timer::create(0.1f);
	timer1->setOnTimerCallback([&](TimerPtr t)->bool {
		cat_x += 20;
		switch (count1 % 3) {
		case 1: cat->setImage("Images/귀여운고양이1.png"); break;
		case 2: cat->setImage("Images/귀여운고양이2.png"); break;
		case 0: cat->setImage("Images/귀여운고양이3.png"); break;
		}
		cat->locate(scene1, cat_x, cat_y);
		printf("move");

		count1++;
		if (cat_x < 600) {

			t->set(0.1f);
			t->start();
		}
		else {
			cat->setImage("Images/식빵고양이.png");
			cat->setScale(1.5f);
			cat->locate(scene1, 800, 60);

			showMessage("이런! 고양이!!");

			button1->hide();
			startButton->setImage("Images/restart.png");
			startButton->show();
			endButton->show();//실패시
			begin = 0;
		}
		return true;
		});
	button1->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (begin) {
			if (hand_g_y >= 150) {
				hand_g_y -= 30;
				hand_grap->locate(scene1, hand_g_x, hand_g_y);
			}
			else {
				showMessage("성공");// 성공시
				timer1->stop();
				button1->hide();
				startButton->setImage("Images/start.png");
				startButton->show();
				endButton->show();
				begin = 0;
				enter = 0;
				game = 0;
			}
		}
		return true;
		});




	//game2
	int bite_x = 0, bite_y = -400;
	auto mouth = Object::create("Images/닫은입.png", scene2, 670, 250, 1);
	auto bite = Object::create("Images/한젓가락.png", scene2, bite_x, bite_y, 1);

	int mouth_open = 0;
	mouth->setOnMouseCallback([&](ObjectPtr, int, int, MouseAction)->bool {
		if (begin) {
			if (!mouth_open) {
				mouth->setImage("Images/열린입.png");
				mouth_open = 1;
			}
			else {
				mouth->setImage("Images/닫은입.png");
				mouth_open = 0;
			}
		}
		return true;
		});
	auto count2 = 0;
	auto timer2 = Timer::create(0.1f);
	timer2->setOnTimerCallback([&](TimerPtr t)->bool {
		bite_x += 10;
		if (bite_y < -100) {
			bite_y += 30;
		}
		else bite_y -= 30;
		bite->locate(scene2, bite_x, bite_y);

		if (bite_x > 300 && bite_x < 400) {
			mouth->setImage("Images/닫은입.png");
			mouth_open = 0;
		}

		count2++;
		if (bite_x < 500) {
			t->set(0.1f);
			t->start();
		}
		else if (mouth_open) {
			showMessage("맛있어!!");
			startButton->setImage("Images/start.png");
			startButton->show();
			endButton->show();
			game = 1;
			begin = 0;
		}
		else {
			showMessage("입을 벌려야지!!");
			startButton->setImage("Images/restart.png");
			startButton->show();
			endButton->show();
			begin = 0;
		}

		return true;
		});



	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (game == 2) {
			begin = 1;
			startButton->hide();
			endButton->hide();

			bite_x = 0, bite_y = -400;

			timer2->set(0.1f);
			timer2->start();
		}
		else if (game == 1) {
			if (!enter) {
				scene1->enter();
				startButton->locate(scene1, 100, 600);
				endButton->locate(scene1, 100, 550);
				enter = 1;
			}
			else {
				begin = 1;
				startButton->hide();
				endButton->hide();
				button1->show();

				cat_x = 0, cat_y = 70;
				hand_g_x = 900, hand_g_y = 600;
				cat->setScale(0.7f);

				timer1->set(0.1f);
				timer1->start();
			}
		}
		else if (game == 0) {
			if (!enter) {
				scene0->enter();
				startButton->locate(scene0, 100, 600);
				endButton->locate(scene0, 100, 550);
				enter = 1;
			}
			else {
				begin = 1;
				startButton->hide();
				endButton->hide();
				button2->show();

				arm_x = -1000, arm_y = 200;
				velocity = 30;
				count0 = 0;
				b_x = 200, b_y = 540;

				timer0->set(0.1f);
				timer0->start();
			}

		}
		else {
			scene2->enter();
			startButton->locate(scene2, 100, 600);
			endButton->locate(scene2, 100, 550);
			game = 2;
		}

		return true;
		});
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});


	startGame(scene3);
	return 0;
}
