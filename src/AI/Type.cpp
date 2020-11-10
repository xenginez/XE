#include "Type.h"

BEG_META( XE::AINodeType )
type->Value( "SUB_NODE", XE::AINodeType::SUB_NODE );
type->Value( "ACTION_NODE", XE::AINodeType::ACTION_NODE );
type->Value( "COMPOSITE_NODE", XE::AINodeType::COMPOSITE_NODE );
type->Value( "CONDITION_NODE", XE::AINodeType::CONDITION_NODE );
type->Value( "DECORATOR_NODE", XE::AINodeType::DECORATOR_NODE );
END_META()

BEG_META( XE::AINodeStatus )
type->Value( "NONE", XE::AINodeStatus::NONE );
type->Value( "RUNNING", XE::AINodeStatus::RUNNING );
type->Value( "SUCCESS", XE::AINodeStatus::SUCCESS );
type->Value( "FAILURE", XE::AINodeStatus::FAILURE );
END_META()

IMPLEMENT_META( XE::AINodeHandle )
IMPLEMENT_META( XE::AIStateHandle )
IMPLEMENT_META( XE::AIElementHandle )
