#include "stdafx.h"
#include "StateManager.h"
#include "GameState.h"

GameState::GameState(StateManager* state_manager_p)
	: m_state_manager_p(state_manager_p)
{
}

GameState::~GameState()
{
}

void GameState::change_state(GameState* new_game_state_p)
{
	m_state_manager_p->change_state(new_game_state_p);
}
