#include "Type.h"

BEG_META( XE::AnimationBlendMode )
type->Value( "ADDITIVE", XE::AnimationBlendMode::ADDITIVE );
type->Value( "OVERRIDE", XE::AnimationBlendMode::OVERRIDE );
END_META()

BEG_META( XE::AnimationStateStatus )
type->Value( "NONE", XE::AnimationStateStatus::NONE );
type->Value( "RUNNING", XE::AnimationStateStatus::RUNNING );
type->Value( "FAILED", XE::AnimationStateStatus::FAILED );
type->Value( "SUCCESS", XE::AnimationStateStatus::SUCCESS );
END_META()
