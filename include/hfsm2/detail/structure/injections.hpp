﻿namespace hfsm2 {
namespace detail {

////////////////////////////////////////////////////////////////////////////////

template <typename TArgs>
class InjectionT {
	template <typename...>
	friend struct B_;

protected:
	using Context		= typename TArgs::Context;

#ifdef HFSM2_ENABLE_UTILITY_THEORY
	using Rank			= typename TArgs::Rank;
	using Utility		= typename TArgs::Utility;
#endif

	using StateList		= typename TArgs::StateList;
	using RegionList	= typename TArgs::RegionList;

	using Control		= ControlT<TArgs>;
	using PlanControl	= PlanControlT<TArgs>;

#ifdef HFSM2_ENABLE_PLANS
	using Plan			= PlanT<TArgs>;
#endif

	using FullControl	= FullControlT <TArgs>;
	using GuardControl	= GuardControlT<TArgs>;

public:
	HFSM2_INLINE void preEntryGuard(Context&)		  noexcept {}

	HFSM2_INLINE void preEnter	   (Context&)		  noexcept {}
	HFSM2_INLINE void preReenter   (Context&)		  noexcept {}

	HFSM2_INLINE void preUpdate	   (Context&)		  noexcept {}

	template <typename TEvent>
	HFSM2_INLINE void preReact	   (const TEvent&,
									Context&)		  noexcept {}

	HFSM2_INLINE void preExitGuard (Context&)		  noexcept {}

	HFSM2_INLINE void postExit	   (Context&)		  noexcept {}

	template <typename T>
	static constexpr StateID  stateId()				  noexcept { return index<StateList, T>();				}

	template <typename T>
	static constexpr RegionID regionId()			  noexcept { return (RegionID) index<RegionList, T>();	}
};

//------------------------------------------------------------------------------

template <typename...>
struct B_;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TFirst, typename... TRest>
struct B_<TFirst, TRest...>
	: TFirst
	, B_<TRest...>
{
	using typename TFirst::Context;

#ifdef HFSM2_ENABLE_UTILITY_THEORY
	using typename TFirst::Rank;
	using typename TFirst::Utility;
#endif

	using typename TFirst::StateList;
	using typename TFirst::RegionList;

	using typename TFirst::Control;
	using typename TFirst::PlanControl;

#ifdef HFSM2_ENABLE_PLANS
	using typename TFirst::Plan;
#endif

	using typename TFirst::FullControl;
	using typename TFirst::GuardControl;

	using TFirst::stateId;
	using TFirst::regionId;

	HFSM2_INLINE void widePreEntryGuard(Context& context)		 noexcept;

	HFSM2_INLINE void widePreEnter	   (Context& context)		 noexcept;
	HFSM2_INLINE void widePreReenter   (Context& context)		 noexcept;

	HFSM2_INLINE void widePreUpdate	   (Context& context)		 noexcept;

	template <typename TEvent>
	HFSM2_INLINE void widePreReact	   (const TEvent& event,
										Context& context)		 noexcept;

	HFSM2_INLINE void widePreExitGuard (Context& context)		 noexcept;

	HFSM2_INLINE void widePostExit	   (Context& context)		 noexcept;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TFirst>
struct B_<TFirst>
	: TFirst
{
	using typename TFirst::Context;

#ifdef HFSM2_ENABLE_UTILITY_THEORY
	using typename TFirst::Rank;
	using typename TFirst::Utility;
#endif

	using typename TFirst::StateList;
	using typename TFirst::RegionList;

	using typename TFirst::Control;
	using typename TFirst::PlanControl;

#ifdef HFSM2_ENABLE_PLANS
	using typename TFirst::Plan;
#endif

	using typename TFirst::FullControl;
	using typename TFirst::GuardControl;

	using TFirst::stateId;
	using TFirst::regionId;

#ifdef HFSM2_ENABLE_UTILITY_THEORY
	HFSM2_INLINE Rank	 rank			  (const Control&)			  noexcept { return Rank	{0};	}
	HFSM2_INLINE Utility utility		  (const Control&)			  noexcept { return Utility{1};		}
#endif

	HFSM2_INLINE void	 entryGuard		  (GuardControl&)			  noexcept {}

	HFSM2_INLINE void	 enter			  (PlanControl&)			  noexcept {}
	HFSM2_INLINE void	 reenter		  (PlanControl&)			  noexcept {}

	HFSM2_INLINE void	 update			  (FullControl&)			  noexcept {}

	template <typename TEvent>
	HFSM2_INLINE void	 react			  (const TEvent&,
						 				   FullControl&)			  noexcept {}

	HFSM2_INLINE void	 exitGuard		  (GuardControl&)			  noexcept {}

	HFSM2_INLINE void	 exit			  (PlanControl&)			  noexcept {}

#ifdef HFSM2_ENABLE_PLANS
	HFSM2_INLINE void	 planSucceeded	  (FullControl& control)	  noexcept { control.succeed();		}
	HFSM2_INLINE void	 planFailed		  (FullControl& control)	  noexcept { control.fail();		}
#endif

	HFSM2_INLINE void	 widePreEntryGuard(Context& context)		  noexcept;

	HFSM2_INLINE void	 widePreEnter	  (Context& context)		  noexcept;
	HFSM2_INLINE void	 widePreReenter   (Context& context)		  noexcept;

	HFSM2_INLINE void	 widePreUpdate	  (Context& context)		  noexcept;

	template <typename TEvent>
	HFSM2_INLINE void	 widePreReact	  (const TEvent& event,
					 	 				   Context& context)		  noexcept;

	HFSM2_INLINE void	 widePreExitGuard (Context& context)		  noexcept;

	HFSM2_INLINE void	 widePostExit	  (Context& context)		  noexcept;
};

//------------------------------------------------------------------------------

template <typename TArgs>
using EmptyT = B_<InjectionT<TArgs>>;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

struct Dynamic_ {};

template <typename... TI>
struct DB_
	: Dynamic_
	, B_<TI...>
{};

template <typename TArgs>
using DynamicEmptyT = DB_<InjectionT<TArgs>>;

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

struct Static_ {};

template <typename... TI>
struct SB_
	: Static_
	, B_<TI...>
{};

template <typename TArgs>
using StaticEmptyT = SB_<InjectionT<TArgs>>;

////////////////////////////////////////////////////////////////////////////////

}
}

#include "injections.inl"
