#include "ship.h"
#include "game.h"
#include "ship_projectile.h"
#include "projectile_move_component.h"

Ship::Ship(Game* game)
    :Actor(game)
	,m_laser_cooldown_period(.25f)
	,m_laser_cooldown_time(0.f)
	,m_alt_laser_cooldown_period(2.f)
	,m_alt_laser_cooldown_time(0.f)
	,m_ic(nullptr)
	,m_asc(nullptr)
	,m_circle(nullptr)
	,m_immortal(false)
{
    std::vector<SDL_Texture*> anim_textures = {
        game->GetTexture("Assets/Ship01.png"),
        game->GetTexture("Assets/Ship02.png"),
        game->GetTexture("Assets/Ship03.png"),
        game->GetTexture("Assets/Ship04.png"),

    };
    m_asc = new AnimSpriteComponent(this);
    m_asc->SetAnimTextures(anim_textures);

	m_ic = new InputComponent(this, 30);
	m_ic->SetMaxForwardSpeed(400.f);
	m_ic->SetMaxAngularSpeed(4.f);
	m_ic->SetForwardKey(SDL_SCANCODE_W);
	m_ic->SetBackKey(SDL_SCANCODE_S);
	m_ic->SetClockWiseKey(SDL_SCANCODE_A);
	m_ic->SetCounterClockWiseKey(SDL_SCANCODE_D);

	m_laser_shoot_key = SDL_SCANCODE_LSHIFT;
	m_alt_laser_shoot_key = SDL_SCANCODE_LALT;

	m_circle = new CircleComponent(this, 50);
	m_circle->SetRadius(static_cast<float>((m_asc->GetTextureHeight() / 2)));
	SDL_Log("Ship: [%p]", this);
}

Ship::~Ship(){
	GetGame()->RemoveShip(this);
}

void Ship::UpdateActor(float deltatime){
	//Separate position and time dependencies updates
	m_laser_cooldown_time -= deltatime;
	m_alt_laser_cooldown_time -= deltatime;

	if(m_laser_cooldown_time < 0) m_laser_cooldown_time = 0.f;
	if(m_alt_laser_cooldown_time < 0) m_alt_laser_cooldown_time = 0.f;
}

void Ship::ActorInput(const bool* state){
	//Separate key state handler
	if(state[m_laser_shoot_key] && !m_laser_cooldown_time){
		m_laser_cooldown_time = m_laser_cooldown_period;

		ShipProjectile* laser = new ShipProjectile(GetGame(), "Assets/Laser.png");
		ProjectileMC* pmc = new ProjectileMC(laser, 30);
		laser->SetMoveStrategy(pmc);
		laser->SetProjectileForwardSpeed(800.f);
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

	}
	if(state[m_alt_laser_shoot_key] && !m_alt_laser_cooldown_time){
		m_alt_laser_cooldown_time = m_alt_laser_cooldown_period;

		ShipProjectile* alt_laser = new ShipProjectile(GetGame(), "Assets/Laser_.png");
		ProjectileMC* pmc = new ProjectileMC(alt_laser, 30);
		alt_laser->SetMoveStrategy(pmc);
		alt_laser->SetProjectileForwardSpeed(400.f);
		alt_laser->SetPosition(GetPosition());
		alt_laser->SetRotation(GetRotation());
		alt_laser->SetPiercing(true);

	}
	
}

void Ship::HandleDamage(){
	SetImmortality(true);
	StartFlickAnimation();
}

void Ship::StartFlickAnimation(){
	if(!m_asc) return;

	m_immortal = true;
	m_asc->SetFlickQty(2 * 5);
	m_asc->SetFlickPeriod(0.25f);
}