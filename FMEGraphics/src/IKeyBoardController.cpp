#include "IKeyBoardController.h"

using namespace FME::Graphics;


void IKeyBoardController::SetControlKeys(const std::vector<char>& keys)
{
	m_keys = keys;
}