#include "Type.h"

BEG_META( XE::NodeStatus )
type->Value( "NONE", XE::NodeStatus::NONE );
type->Value( "RUNNING", XE::NodeStatus::RUNNING );
type->Value( "SUCCESS", XE::NodeStatus::SUCCESS );
type->Value( "FAILURE", XE::NodeStatus::FAILURE );
END_META()

BEG_META( XE::ConditionStatus )
type->Value( "ONCE", XE::ConditionStatus::ONCE );
type->Value( "ALWAYS", XE::ConditionStatus::ALWAYS );
END_META()

IMPLEMENT_META( XE::AINodeHandle )
IMPLEMENT_META( XE::AIStateHandle )
