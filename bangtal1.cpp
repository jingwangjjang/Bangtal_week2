#include <bangtal.h>
using namespace bangtal;

int main() {
    SoundPtr sound = Sound::create("Sound/bgm.mp3");
    sound->play();

    ScenePtr scene1 = Scene::create("첫번째 방", "RoomEscape/배경-1.png");
    ScenePtr scene2 = Scene::create("두번째 방", "RoomEscape/배경-2.png");

    auto crush = Object::create("RoomEscape/균열1.png", scene1, 800, 500);
    auto hammer = Object::create("RoomEscape/망치.png", scene1, 200, 100);
    auto seulgi = Object::create("RoomEscape/슬기.jpg", scene1, 150, 400);
    seulgi->setScale(0.5f);
    hammer->setScale(0.4f);
    int crush_touch = 1; 
    bool hammer_handed = false;

    crush->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (crush_touch == 1 && hammer_handed == true) {
            crush->setImage("RoomEscape/균열2.png");
            showMessage("콰직!");
            crush_touch++;
        }
        else if (crush_touch == 2 && hammer_handed == true) {
            crush->setImage("RoomEscape/균열3.png");
            showMessage("콰지직!");
            crush_touch++;
        }
        else if (crush_touch == 3 && hammer_handed == true) {
            crush->setImage("RoomEscape/구멍.png");
            showMessage("쿵!!!");
            crush_touch++;
        }
        else if (crush_touch == 4) {
            scene2->enter();
        }
        else {
            showMessage("망치로 부셔질 것 같은 벽이다.");
        }

        return true;
    });

    hammer->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        hammer->pick();
        hammer_handed = true;
        showMessage("망치를 획득했다.");
        return true;
    });

    auto hole = Object::create("RoomEscape/구멍.png", scene2, 100, 300);
    auto drawer = Object::create("RoomEscape/서랍.png", scene2, 450, 240);
    auto door = Object::create("RoomEscape/문-오른쪽-닫힘.png", scene2, 910, 270);
    auto halfkey1 = Object::create("RoomEscape/열쇠1.png", scene2, 100, 100, false);
    auto halfkey2 = Object::create("RoomEscape/열쇠2.png", scene2, 1150, 200);
    auto plant = Object::create("RoomEscape/화분.png", scene2, 1100, 200);
    auto key = Object::create("RoomEscape/열쇠.png", scene2, 100, 100, false);
    bool key_handed = false;
    bool door_open = false;
    bool drawer_open = false;
    drawer->setScale(0.25f);
    halfkey2->setScale(0.08f);

    hole->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        scene1->enter();
        return true;
    });

    drawer->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        showKeypad("200210", drawer);
        return true;
    });


    door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (key_handed && door_open == false) {
            door->setImage("RoomEscape/문-오른쪽-열림.png");
            door_open = true;
        }
        else if (door_open) {
            endGame();
        }
        else {
            showMessage("문이 잠겨있다.");
        }
        return true;
    });

    halfkey2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        halfkey2->pick();
        showMessage("열쇠조각2을 획득했다.");
        return true;
    });

    drawer->setOnKeypadCallback([&](ObjectPtr object)->bool {
        if (drawer_open == false) {
            drawer->setImage("RoomEscape/열린서랍.png");
            halfkey1->pick();
            showMessage("열쇠조각1을 획득했다.");
            drawer_open = true;
        }
        return true;
    });

    plant->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        if (action == MouseAction::MOUSE_DRAG_RIGHT) {
            plant->locate(scene2, 1200, 200);
        }
        return true;
    });
    
    key->defineCombination(halfkey1, halfkey2);

    key->setOnCombineCallback([&](ObjectPtr object)->bool {
        key_handed = true;
        return true;
    });

    startGame(scene1);

    return 0;
}