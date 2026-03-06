#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiSmartPointer.h"
#include "RE/N/NiTArray.h"
#include "RE/N/NiTCollection.h"

namespace RE
{
	class NiAVObject;

	class NiPick
	{
	public:
		class Record
		{
		public:
			// members
			NiPointer<NiAVObject> object;     // 00
			NiPoint3              intersect;  // 08
			NiPoint3              normal;     // 14
			float                 distance;   // 20
			std::uint32_t         pad24;      // 24
		};
		static_assert(sizeof(Record) == 0x28);

		enum class PickType : std::uint32_t
		{
			FIND_ALL = 0,
			FIND_FIRST = 1
		};

		enum class SortType : std::uint32_t
		{
			SORT = 0,
			NO_SORT = 1
		};

		enum class IntersectType : std::uint32_t
		{
			BOUND_INTERSECT = 0,
			TRIANGLE_INTERSECT = 1
		};

		enum class CoordinateType : std::uint32_t
		{
			MODEL_COORDINATES = 0,
			WORLD_COORDINATES = 1
		};

		struct Deleter
		{
			void operator()(NiPick* a_pick) const
			{
				if (a_pick) {
					a_pick->Destroy();
				}
			}
		};

		using Ptr = std::unique_ptr<NiPick, Deleter>;

		[[nodiscard]] static Ptr Create(std::uint32_t a_initialSize = 0, std::uint32_t a_growBy = 1);
		void                     Destroy();

		bool PickObjects(const NiPoint3& a_origin, const NiPoint3& a_direction, bool a_append = false);

		// members
		REX::EnumSet<PickType, std::uint32_t>       pickType;            // 00
		REX::EnumSet<SortType, std::uint32_t>       sortType;            // 04
		REX::EnumSet<IntersectType, std::uint32_t>  intersectType;       // 08
		REX::EnumSet<CoordinateType, std::uint32_t> coordinateType;      // 0C
		bool                                        frontOnly;           // 10
		bool                                        observeAppCullFlag;  // 11
		bool                                        returnNormal;        // 12
		bool                                        returnSmoothNormal;  // 13
		bool                                        returnTexture;       // 14
		bool                                        returnColor;         // 15
		std::uint16_t                               pad16;               // 16
		NiPointer<NiAVObject>                       root;                // 18
		NiTScrapArray<Record*>                      pickResults;         // 20
		NiPoint3                                    origin;              // 38
		NiPoint3                                    direction;           // 44

	private:
		NiPick() = delete;
		~NiPick() = delete;

		NiPick* ctor(std::uint32_t a_initialSize, std::uint32_t a_growBy);
		void    dtor();
	};
	static_assert(sizeof(NiPick) == 0x50);
}
