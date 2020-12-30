#include "Type.h"

BEG_META( Animation::BlendMode )
type->Value( "ADDITIVE", Animation::BlendMode::ADDITIVE );
type->Value( "OVERRIDE", Animation::BlendMode::OVERRIDE );
END_META()

BEG_META( Animation::StateStatus )
type->Value( "NONE", Animation::StateStatus::NONE );
type->Value( "RUNNING", Animation::StateStatus::RUNNING );
type->Value( "FAILED", Animation::StateStatus::FAILED );
type->Value( "SUCCESS", Animation::StateStatus::SUCCESS );
END_META()
