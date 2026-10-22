// AutoDeco - skeleton. Chinh object ID/style trong STYLES de mo rong.
#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <vector>
#include <string>
#include <cmath>

using namespace geode::prelude;

struct DecoStyle {
    std::string name;
    int objectId;      // object dung de deco
    float density;     // so object moi beat
    float yRange;      // do cao vung deco
    float scale;
};

// Them style moi o day (hoac doc tu JSON sau)
static const std::vector<DecoStyle> STYLES = {
    {"Minimal Glow", 1, 1.f, 60.f, 0.5f},
    {"Dense Block", 1, 4.f, 120.f, 0.8f},
    {"Pulse Wave", 1, 2.f, 90.f, 0.6f},
};

// Toc do 1x trong GD ~ 311.58 unit/giay
static constexpr float SPEED_1X = 311.58f;

class $modify(AutoDecoUI, EditorUI) {
    struct Fields {
        int styleIndex = 0;
        float bpm = 120.f;
        float startX = 0.f;
        int beats = 32;
        int doneBeats = 0;
        bool running = false;
        std::vector<GameObject*> added; // de show/xoa phan da them
    };

    bool init(LevelEditorLayer* layer) {
        if (!EditorUI::init(layer)) return false;

        auto menu = CCMenu::create();
        auto spr = ButtonSprite::create("Deco");
        auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(AutoDecoUI::onDeco));
        menu->addChild(btn);
        auto win = CCDirector::get()->getWinSize();
        menu->setPosition({win.width - 40.f, win.height - 30.f});
        this->addChild(menu, 100);
        return true;
    }

    void onDeco(CCObject*) {
        auto f = m_fields.self();
        if (f->running) return;
        // Doi style moi lan bam (thay bang popup chon style sau)
        f->styleIndex = (f->styleIndex + 1) % STYLES.size();
        f->doneBeats = 0;
        f->startX = 0.f;
        f->running = true;
        Notification::create("Deco: " + STYLES[f->styleIndex].name,
                             NotificationIcon::Loading)->show();
        this->schedule(schedule_selector(AutoDecoUI::tick), 0.f);
    }

    // Chia nho theo frame de GUI khong dung
    void tick(float) {
        auto f = m_fields.self();
        auto const& st = STYLES[f->styleIndex];
        float beatLen = 60.f / f->bpm;          // giay / beat
        float beatX = beatLen * SPEED_1X;       // unit / beat

        // 2 beat moi frame
        for (int b = 0; b < 2 && f->doneBeats < f->beats; ++b, ++f->doneBeats) {
            float x = f->startX + f->doneBeats * beatX;
            int n = std::max(1, (int)std::round(st.density));
            for (int i = 0; i < n; ++i) {
                float y = 30.f + (st.yRange * i / n);
                auto obj = m_editorLayer->createObject(st.objectId, {x + i * (beatX / n), y}, false);
                if (obj) {
                    obj->setScale(st.scale);
                    f->added.push_back(obj);
                }
            }
        }

        if (f->doneBeats >= f->beats) {
            this->unschedule(schedule_selector(AutoDecoUI::tick));
            f->running = false;
            Notification::create("Xong: " + std::to_string(f->added.size()) + " object",
                                 NotificationIcon::Success)->show();
        }
    }
};
