#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "StateManager.h"

StateManager::StateManager()
	: m_current_state_p(NULL)
{
	change_state(MenuState::get_instance(this));
}

StateManager::~StateManager()
{

}

void StateManager::change_state(GameState* new_game_state_p)
{
	if(m_current_state_p)
		m_current_state_p->leave_state();
	m_current_state_p = new_game_state_p;
	m_current_state_p->enter_state();
}

GameState* StateManager::get_current_state()
{
	return m_current_state_p;
}

void StateManager::on_keyup(WPARAM w_param)
{
	if(m_current_state_p)
		m_current_state_p->on_keyup(w_param);
	else
		throw Exception("StateManager::on_keyup(WPARAM w_param) - m_current_state_p is NULL");
}

void StateManager::on_keydown(WPARAM w_param)
{
	if(m_current_state_p)
		m_current_state_p->on_keydown(w_param);
	else
		throw Exception("StateManager::on_keydown(WPARAM w_param) - m_current_state_p is NULL");
}

void StateManager::on_mouse_left_button_click(WPARAM x_coordinate, WPARAM y_coordinate)
{
	if(m_current_state_p)
		m_current_state_p->on_mouse_left_button_click(x_coordinate, y_coordinate);
	else
		throw Exception("StateManager::on_keydown(WPARAM w_param) - m_current_state_p is NULL");
}

void StateManager::on_mouse_left_button_release(WPARAM x_coordinate, WPARAM y_coordinate)
{
	if(m_current_state_p)
		m_current_state_p->on_mouse_left_button_release(x_coordinate, y_coordinate);
	else
		throw Exception("StateManager::on_keydown(WPARAM w_param) - m_current_state_p is NULL");
}

void StateManager::on_mouse_move(WPARAM x_coordinate, WPARAM y_coordinate)
{
	if(m_current_state_p)
		m_current_state_p->on_mouse_move(x_coordinate, y_coordinate);
	else
		throw Exception("StateManager::on_keydown(WPARAM w_param) - m_current_state_p is NULL");
}

void StateManager::update(DWORD current_time)
{
	if(m_current_state_p)
		m_current_state_p->update(current_time);
	else
		throw Exception("StateManager::update(WPARAM w_param) - m_current_state_p is NULL");
}

void StateManager::draw()
{
	if(m_current_state_p)
		m_current_state_p->draw();
	else
		throw Exception("StateManager::draw(WPARAM w_param) - m_current_state_p is NULL");
}
