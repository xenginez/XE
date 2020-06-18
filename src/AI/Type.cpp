#include "Type.h"



BEG_META( XE::NodeStatus )
type->Value( "None", XE::NodeStatus::None );
type->Value( "Running", XE::NodeStatus::Running );
type->Value( "Success", XE::NodeStatus::Success );
type->Value( "Failure", XE::NodeStatus::Failure );
type->Value( "Finish", XE::NodeStatus::Finish );
END_META()

BEG_META( XE::ConditionStatus )
type->Value( "Once", XE::ConditionStatus::Once );
type->Value( "Always", XE::ConditionStatus::Always );
END_META()

IMPLEMENT_META( XE::NodeHandle )
IMPLEMENT_META( XE::StateHandle )
