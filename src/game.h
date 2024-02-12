#pragma once

#include "App.h"
#include <vector>
#include <random>
#include "bunker.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 720;
const int RECT_WIDTH = 52;
const int RECT_HEIGHT = 35;
float MOVE_INTERVAL = 0.01f;
const float MOVE_DISTANCE = 3.f;
const int MOVE_DISTANCE_Y = RECT_HEIGHT / 2;
const int PADDING_X = 60;
const int PADDING_Y = 50;

const int PLAYER_SPEED = 245;

int position = 1;

// Initialize rectangle positions
int rows = 5;
int cols = 11;
std::vector<SDL_FRect> enemies;
std::vector<SDL_FRect> enemy_hitboxes;
std::vector<int> enemy_status;

SDL_FRect playa = {80, 660, 52 + 50, 35 + 10};
int kill_count = 0;

bool tick_bool = true;

// Frame counters for each rectangle
float frameCount = 0.0f;

float second = 0.f;
int second_count = 0;

std::vector<int> dead_enemies;
std::vector<float> dead_counts;

const SDL_FRect getSprite(int i, int j)
{
    return {2.f + (110 * i), 18.f + (120 * j), 109.f, 81.f};
}

const Uint8 *keys = SDL_GetKeyboardState(NULL);

std::vector<SDL_FRect> bullets;
std::vector<SDL_FRect> enemy_bullets;

float enemy_bullet_cooldown = 0.f;
bool enemy_can_shoot = true;

bool player_alive = true;
float player_dead_cooldown = 0.f;

int level = 1;
int lives = 3;
int score = 0;

std::vector<SDL_FRect> bunker;
std::vector<std::vector<SDL_FRect>> bunker1;
std::vector<std::vector<SDL_FRect>> bunker2;
std::vector<std::vector<SDL_FRect>> bunker3;
std::vector<std::vector<SDL_FRect>> bunker4;

float cooldown_count = 0.f;
bool cooldown = false;

void startGame(int level)
{
    if (cooldown)
        return;

    enemies.clear();
    kill_count = 0;
    position = 1;
    MOVE_INTERVAL = 0.5f - (0.02f * level);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            SDL_FRect rect = {(SCREEN_WIDTH - 652) / 2, (MOVE_DISTANCE_Y) * (9.f + level), RECT_WIDTH, RECT_HEIGHT};
            rect.x += PADDING_X * j;
            rect.y += PADDING_Y * i;
            enemies.emplace_back(rect);
        }
    }

    enemy_status.assign(rows * cols, 1);
    enemy_hitboxes = enemies;
}

void resetGame()
{
    enemy_bullet_cooldown = 0.f;
    enemy_bullets.clear();

    bunker1.resize(28);
    bunker2.resize(28);
    bunker3.resize(28);
    bunker4.resize(28);
    bunker = getBunkerRects(100, 550, 4);
    fragments(bunker, bunker1);
    bunker = getBunkerRects(275, 550, 4);
    fragments(bunker, bunker2);
    bunker = getBunkerRects(475, 550, 4);
    fragments(bunker, bunker3);
    bunker = getBunkerRects(650, 550, 4);
    fragments(bunker, bunker4);

    lives = 3;
    level = 1;
    startGame(level);
    score = 0;
}

void updateAndRenderGame(App *app, float deltaTime, SDL_Texture *sheet)
{
    SDL_Renderer *renderer = app->GetSDLRenderer();
    if (kill_count >= enemies.size())
        cooldown = true;

    if (MOVE_INTERVAL < 0.01f)
        MOVE_INTERVAL = 0.01f;

    if (keys[SDL_SCANCODE_RIGHT] && playa.x + 20 < SCREEN_WIDTH - playa.w + 40 && player_alive)
        playa.x += PLAYER_SPEED * deltaTime;
    if (keys[SDL_SCANCODE_LEFT] && playa.x + 20 > 0 && player_alive)
        playa.x -= PLAYER_SPEED * deltaTime;

    SDL_FRect playa_hitbox = {playa.x + 20, playa.y + 22, playa.w + -40, playa.h - 20};
    if (keys[SDL_SCANCODE_SPACE] && bullets.size() < 1 && player_alive)
        bullets.push_back({playa_hitbox.x + playa_hitbox.w / 2 - 2.5f, playa_hitbox.y - playa_hitbox.h + 5.f, 4.f, 15.f});

    if (cooldown)
        cooldown_count += deltaTime;

    if (cooldown_count >= 1.f)
    {
        cooldown_count = 0.f;
        cooldown = false;
        lives++;
        startGame(++level);
    }

    second += deltaTime;
    if (second >= 1.f)
    {
        second -= 1.f;
        second_count++;
    }

    if (!player_alive)
    {
        player_dead_cooldown += deltaTime;
    }
    if (player_dead_cooldown >= 1.5f)
    {
        player_alive = true;
        playa = {80, 660, 52 + 50, 35 + 10};
        player_dead_cooldown = 0.f;
    }

    if (enemy_bullets.size() == 3)
        enemy_can_shoot = false;
    if (!enemy_can_shoot)
        enemy_bullet_cooldown += deltaTime;
    if (enemy_bullet_cooldown >= 1.5f)
    {
        enemy_bullet_cooldown = 0;
        enemy_can_shoot = true;
    }

    // Move rectangle 1 every MOVE_INTERVAL_1 seconds
    frameCount += deltaTime;
    if (frameCount >= MOVE_INTERVAL)
    {
        frameCount -= MOVE_INTERVAL; // Adjust frame counter

        tick_bool = !tick_bool;

        for (int j = 0; j < enemies.size() && player_alive; j++)
            enemies[j].x += MOVE_DISTANCE * position;

        for (int i = 0; i < enemies.size() && player_alive; i++)
        {
            if (enemy_status[i] == 0)
                continue;

            if (enemies[i].x > SCREEN_WIDTH - RECT_WIDTH || enemies[i].x < 0)
            {
                position *= -1;
                for (int j = 0; j < enemies.size(); j++)
                {
                    enemies[j].y += MOVE_DISTANCE_Y;
                    enemies[j].x += MOVE_DISTANCE * position;
                }
                SDL_Log("%d seconds", second_count);
                second_count = 0;
            }
        }

        enemy_hitboxes = enemies;
        for (int i = 0; i < 11; i++)
        {
            enemy_hitboxes[i].w = RECT_WIDTH - 10;
            enemy_hitboxes[i].x = enemies[i].x + 5;
        }
    }

    for (size_t i = 0; i < bullets.size(); i++)
    {
        for (size_t j = 0; j < enemies.size(); j++)
        {
            if (SDL_HasRectIntersectionFloat(&bullets[i], &enemy_hitboxes[j]) && enemy_status[j] == 1)
            {
                bullets.erase(bullets.begin() + i);
                enemy_status[j] = 2;
                dead_enemies.push_back((int)j);
                dead_counts.push_back(0.f);
                MOVE_INTERVAL -= 0.0005f * level;
                SDL_Log("dead %f", MOVE_INTERVAL);
                kill_count++;

                if (j <= 10)
                {
                    score += 40;
                    continue;
                }
                if (j <= 32)
                {
                    score += 20;
                    continue;
                }
                if (j <= 54)
                    score += 10;
            }
        }
    }

    for (size_t i = 0; i < enemy_bullets.size(); i++)
    {
        if (SDL_HasRectIntersectionFloat(&enemy_bullets[i], &playa_hitbox) && player_alive == true)
        {
            player_alive = false;
            enemy_can_shoot = false;
            lives--;

            enemy_bullet_cooldown = 0.f;
            enemy_bullets.erase(enemy_bullets.begin() + i);
            if (lives == 0)
            {
                bunker1.resize(28);
                bunker2.resize(28);
                bunker3.resize(28);
                bunker4.resize(28);
                bunker = getBunkerRects(100, 550, 4);
                fragments(bunker, bunker1);
                bunker = getBunkerRects(275, 550, 4);
                fragments(bunker, bunker2);
                bunker = getBunkerRects(475, 550, 4);
                fragments(bunker, bunker3);
                bunker = getBunkerRects(650, 550, 4);
                fragments(bunker, bunker4);
                lives = 3;
                level = 1;
                enemy_bullets.clear();
                startGame(level);
                score = 0;
                break;
            }
        }
    }

    for (size_t i = 0; i < bullets.size(); i++)
    {
        bool erased = false;
        for (size_t j = 0; j < bunker1.size(); j++)
        {
            for (size_t k = 0; k < bunker1[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&bullets[i], &bunker1[j][k]))
                {
                    bunker1.erase(bunker1.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        for (size_t j = 0; j < bunker2.size(); j++)
        {
            for (size_t k = 0; k < bunker2[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&bullets[i], &bunker2[j][k]))
                {
                    bunker2.erase(bunker2.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        for (size_t j = 0; j < bunker3.size(); j++)
        {
            for (size_t k = 0; k < bunker3[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&bullets[i], &bunker3[j][k]))
                {
                    bunker3.erase(bunker3.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        for (size_t j = 0; j < bunker4.size(); j++)
        {
            for (size_t k = 0; k < bunker4[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&bullets[i], &bunker4[j][k]))
                {
                    bunker4.erase(bunker4.begin() + j);
                    bullets.erase(bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        if (erased)
            break;
    }

    for (size_t i = 0; i < enemy_bullets.size(); i++)
    {
        bool erased = false;
        for (size_t j = 0; j < bunker1.size(); j++)
        {
            for (size_t k = 0; k < bunker1[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&enemy_bullets[i], &bunker1[j][k]))
                {
                    bunker1.erase(bunker1.begin() + j);
                    enemy_bullets.erase(enemy_bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        for (size_t j = 0; j < bunker2.size(); j++)
        {
            for (size_t k = 0; k < bunker2[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&enemy_bullets[i], &bunker2[j][k]))
                {
                    bunker2.erase(bunker2.begin() + j);
                    enemy_bullets.erase(enemy_bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        for (size_t j = 0; j < bunker3.size(); j++)
        {
            for (size_t k = 0; k < bunker3[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&enemy_bullets[i], &bunker3[j][k]))
                {
                    bunker3.erase(bunker3.begin() + j);
                    enemy_bullets.erase(enemy_bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        for (size_t j = 0; j < bunker4.size(); j++)
        {
            for (size_t k = 0; k < bunker4[j].size(); k++)
            {
                if (SDL_HasRectIntersectionFloat(&enemy_bullets[i], &bunker4[j][k]))
                {
                    bunker4.erase(bunker4.begin() + j);
                    enemy_bullets.erase(enemy_bullets.begin() + i);
                    erased = true;
                    break;
                }
            }
            if (erased)
                break;
        }
        if (erased)
            break;
    }

    app->DrawString(std::to_string(lives), {10, 10}, 200, {0, 1, 0, 1}, 1);
    app->DrawString(std::string("Score " + std::to_string(score)), {300, 10}, 200, {1, 1, 1, 1}, 2);

    std::random_device rd;                                                // obtain a random number from hardware
    std::mt19937 gen(rd());                                               // seed the generator
    std::uniform_int_distribution<> enemy_bullet(0, (int)enemies.size()); // define the range
    int enemy_index = enemy_bullet(gen);
    if (enemy_status[enemy_index] == 1 && enemy_index < 11)
    {
        if (enemy_bullets.size() < 3 && enemy_can_shoot)
        {
            enemy_bullets.push_back({enemy_hitboxes[enemy_index].x + enemy_hitboxes[enemy_index].h / 2, enemy_hitboxes[enemy_index].y, 4.f, 15.f});
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (size_t i = 0; i < bunker1.size(); i++)
        SDL_RenderFillRects(renderer, bunker1[i].data(), (int)bunker1[i].size());
    for (size_t i = 0; i < bunker2.size(); i++)
        SDL_RenderFillRects(renderer, bunker2[i].data(), (int)bunker2[i].size());
    for (size_t i = 0; i < bunker3.size(); i++)
        SDL_RenderFillRects(renderer, bunker3[i].data(), (int)bunker3[i].size());
    for (size_t i = 0; i < bunker4.size(); i++)
        SDL_RenderFillRects(renderer, bunker4[i].data(), (int)bunker4[i].size());

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (size_t i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].y < 0.f)
        {
            bullets.erase(bullets.begin() + i);
            continue;
        }

        bullets[i].y -= 600.f * deltaTime;
    }
    SDL_RenderFillRects(renderer, bullets.data(), (int)bullets.size());

    for (size_t i = 0; i < enemy_bullets.size(); i++)
    {
        if (enemy_bullets[i].y > SCREEN_HEIGHT)
        {
            enemy_bullets.erase(enemy_bullets.begin() + i);
            continue;
        }

        enemy_bullets[i].y += 500.f * deltaTime;
    }
    SDL_RenderFillRects(renderer, enemy_bullets.data(), (int)enemy_bullets.size());

    // Draw the rectangles
    // SDL_SetRenderDrawColor(renderer, color.x, color.y, color.w, color.h); // Red for rectangle 1
    // SDL_RenderFillRects(renderer, enemy_hitboxes.data(), rows * cols);

    int which = 3;
    for (size_t i = 0; i < enemies.size(); i++)
    {
        if (enemy_status[i] == 0)
            continue;
        if (enemy_status[i] == 2)
        {
            if (enemies[i].h != RECT_HEIGHT + 10)
            {
                enemies[i].y -= 10;
                enemies[i].x -= 5;
            }
            enemies[i].h = RECT_HEIGHT + 10;
            enemies[i].w = RECT_WIDTH + 10;
            SDL_RenderTexture(renderer, sheet, &getSprite(7, 2), &enemies[i]);
            for (size_t j = 0; j < dead_enemies.size(); j++)
                if (i == dead_enemies[j])
                    dead_counts[j] += deltaTime;
            continue;
        }

        if (i / 11 >= 1)
            which = 1;
        if (i / 11 >= 3)
            which = 5;

        SDL_RenderTexture(renderer, sheet, &getSprite(tick_bool ? which : which + 1, 0), &enemies[i]);
    }

    for (size_t i = 0; i < dead_counts.size(); i++)
    {
        if (dead_counts[i] >= 0.2f)
        {
            enemy_status[dead_enemies[i]] = 0;
            dead_enemies.erase(dead_enemies.begin() + i);
            dead_counts.erase(dead_counts.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < enemy_hitboxes.size(); i++)
    {
        if (enemy_hitboxes[i].y >= (MOVE_DISTANCE_Y) * (9.f + 29))
        {
            enemy_bullet_cooldown = 0.f;
            enemy_bullets.clear();

            bunker1.resize(28);
            bunker2.resize(28);
            bunker3.resize(28);
            bunker4.resize(28);
            bunker = getBunkerRects(100, 550, 4);
            fragments(bunker, bunker1);
            bunker = getBunkerRects(275, 550, 4);
            fragments(bunker, bunker2);
            bunker = getBunkerRects(475, 550, 4);
            fragments(bunker, bunker3);
            bunker = getBunkerRects(650, 550, 4);
            fragments(bunker, bunker4);

            lives = 3;
            level = 1;
            startGame(level);
            score = 0;
            break;
        }
    }

    SDL_RenderTexture(renderer, sheet, &getSprite(player_alive ? 4 : 5, 2), &playa);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
}
