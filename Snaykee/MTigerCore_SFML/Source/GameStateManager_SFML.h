#pragma once
#include <stack>
#include <memory>
#include "GameState_SFML.h"

namespace MR_SFML
{
	class GameStateManager_SFML
	{
	public:
		GameStateManager_SFML() = default;
		~GameStateManager_SFML() = default;

		/// <summary>
		/// Adds a new game state.
		/// </summary>
		/// <param name="newState">The state being added.</param>
		/// <param name="replacingCurrState">Is current state being replaced by the state (new) that is being added.</param>
		void AddState(std::unique_ptr<GameState_SFML> newState, bool replacingCurrState = true);

		/// <summary>
		/// Removes the top state.
		/// </summary>
		void RemoveState();

		/// <summary>
		/// Logic for when there is a change in states.
		/// </summary>
		void HandleStateChange();

		/// <summary>
		/// Get and return the top (current) state.
		/// </summary>
		/// <returns></returns>
		std::unique_ptr<GameState_SFML>& Get_CurrentActiveState();

	private:
		bool _isRemovingState = false;
		bool _isAddingState = false;
		bool _isReplacingState = false;

		/// <summary>
		/// Contains/holds game states.
		/// </summary>
		std::stack<std::unique_ptr<GameState_SFML>> _statesStack;

		std::unique_ptr<GameState_SFML> _newState = nullptr;
	};
}
