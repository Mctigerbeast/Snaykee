#include "GameStateManager_SFML.h"

namespace MR_SFML
{
	void GameStateManager_SFML::AddState(std::unique_ptr<GameState_SFML> newState, bool replacingCurrState)
	{
		this->_isAddingState = true;
		this->_isReplacingState = replacingCurrState;
		this->_newState = std::move(newState);
	}

	void GameStateManager_SFML::RemoveState()
	{
		this->_isRemovingState = true;
	}

	void GameStateManager_SFML::HandleStateChange()
	{
		if (this->_isRemovingState && !this->_statesStack.empty())
		{
			this->_statesStack.pop();

			if (!this->_statesStack.empty())
				this->_statesStack.top()->StartState();

			this->_isRemovingState = false;
		}

		if (this->_isAddingState)
		{
			if (!this->_statesStack.empty())
			{
				if (this->_isReplacingState)
					this->_statesStack.pop();
				else
					this->_statesStack.top()->PauseState();
			}
			
			// Add new state to the stack
			this->_statesStack.push(std::move(this->_newState));
			this->_statesStack.top()->Initialize();
			this->_isAddingState = false;
		}
	}

	std::unique_ptr<GameState_SFML>& GameStateManager_SFML::Get_CurrentActiveState()
	{
		return this->_statesStack.top();
	}
}
