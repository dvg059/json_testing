
#include "../include/json_mngr.h"
#include "../include/LOG.H"
#include "../json/json.h"
#include <gtest/gtest.h>

namespace {

// The fixture for testing class leetcode_bsttree.
TEST(CJsonMngr , keyMngr) {
	CJsonMngr jsonMngr;
	rules_rec rec;

	string  expected_keys[]={"CTA10", "CTA00", "CTA11","MR00", "MR01", "MR11"}; // expected key results
	string module[]={"CTA", "CTA", "CTA","MR", "MR", "MR"};
	bool engine_enabled[]={true,false,true,false, false,true};		// engine enabled states
	bool engine_triggered[]={false,false,true,false,true,true};		// engine triggered states

	for (unsigned i=0; i < 6; ++i)
	{
		rec.module= module[i];
		rec.rulesEngineEnabled=engine_enabled[i];
		rec.rulesEngineTriggered=engine_triggered[i];

		string ky = jsonMngr.create_tbl_key(rec);
		EXPECT_EQ(ky, expected_keys[i]);

	} // end for loop

} // end test

}  // namespace


/********************************************/
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}