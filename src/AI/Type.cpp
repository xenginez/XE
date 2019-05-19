#include "Type.h"

USING_XE

BEG_META( NodeStatus )
type->Value( "None", NodeStatus::None );
type->Value( "Running", NodeStatus::Running );
type->Value( "Success", NodeStatus::Success );
type->Value( "Failure", NodeStatus::Failure );
type->Value( "Finish", NodeStatus::Finish );
END_META()

BEG_META( ConditionStatus )
type->Value( "Once", ConditionStatus::Once );
type->Value( "Always", ConditionStatus::Always );
END_META()

BEG_META( NodeHandle )
END_META()

BEG_META( StateHandle )
END_META()
