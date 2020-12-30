#include "Type.h"

BEG_META( AI::AINodeType )
type->Value( "SUB_NODE", AI::AINodeType::SUB_NODE );
type->Value( "ACTION_NODE", AI::AINodeType::ACTION_NODE );
type->Value( "COMPOSITE_NODE", AI::AINodeType::COMPOSITE_NODE );
type->Value( "CONDITION_NODE", AI::AINodeType::CONDITION_NODE );
type->Value( "DECORATOR_NODE", AI::AINodeType::DECORATOR_NODE );
END_META()

BEG_META( AI::AINodeStatus )
type->Value( "NONE", AI::AINodeStatus::NONE );
type->Value( "RUNNING", AI::AINodeStatus::RUNNING );
type->Value( "SUCCESS", AI::AINodeStatus::SUCCESS );
type->Value( "FAILURE", AI::AINodeStatus::FAILURE );
END_META()

IMPLEMENT_META( AI::AINodeHandle )
IMPLEMENT_META( AI::AIStateHandle )
IMPLEMENT_META( AI::AIElementHandle )

IMPLEMENT_META_MODULE( AI );