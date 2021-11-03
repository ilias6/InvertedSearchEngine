#include <gtest/gtest.h>
#include "../include/word.hpp"


TEST(ExactMatchTest, NotEqual) {
    Word w1("a");
    Word w2("b");
    EXPECT_EQ(false, w1.exactMatch(w2));
    w1.set("aaabb");
    w2.set("ubbcc");
    EXPECT_EQ(false, w1.exactMatch(w2));
    w1.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    EXPECT_EQ(false, w1.exactMatch(w2));
    w2.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w1.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    EXPECT_EQ(false, w1.exactMatch(w2));
}

TEST(ExactMatchTest, Equal) {
    Word w1("a");
    Word w2("a");
    EXPECT_EQ(true, w1.exactMatch(w2));
    w1.set("aaabb");
    w2.set("aaabb");
    EXPECT_EQ(true, w1.exactMatch(w2));
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    EXPECT_EQ(true, w1.exactMatch(w2));
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    EXPECT_EQ(true, w1.exactMatch(w2));
}


TEST(ExactMatchTest, Empty) { 
    Word w1("a");
    Word w2("");
    EXPECT_EQ(false, w1.exactMatch(w2));
    w1.set("");
    w2.set("aaabb");
    EXPECT_EQ(false, w1.exactMatch(w2));
    w1.set("");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    EXPECT_EQ(false, w1.exactMatch(w2));
}

TEST(hammingDistanceTest, NotEqual) {
    Word w1("a");
    Word w2("b");
    EXPECT_EQ(1, w1.hammingDist(w2));
    w1.set("aaabb");
    w2.set("ubbcc");
    EXPECT_EQ(5, w1.hammingDist(w2));
    w1.set("kjhgfyuiokbgft&*GTijhbvft67ihGt7ijhgFT^&*IUYFGHJki76ytFCVJI&^TFVBJ");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67ui");
    EXPECT_EQ(66, w1.hammingDist(w2));
}

TEST(hammingDistanceTest, Equal) {
    Word w1("a");
    Word w2("a");
    EXPECT_EQ(0, w1.hammingDist(w2));
    w1.set("aaabb");
    w2.set("aaabb");
    EXPECT_EQ(0, w1.hammingDist(w2));
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    EXPECT_EQ(0, w1.hammingDist(w2));
}

TEST(hammingDistanceTest, DiffLength) { 
    Word w1("a");
    Word w2("");
    EXPECT_EQ(-1, w1.hammingDist(w2));
    w1.set("");
    w2.set("aaabb");
    EXPECT_EQ(-1, w1.hammingDist(w2));
    w1.set("");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    EXPECT_EQ(-1, w1.hammingDist(w2));
    w1.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    EXPECT_EQ(-1, w1.hammingDist(w2));
    w2.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w1.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    EXPECT_EQ(-1, w1.hammingDist(w2));
}

TEST(EditDistanceTest, NotEqual) {
    Word w1("a");
    Word w2("b");
    EXPECT_EQ(1, w1.editDist(w2));
    w1.set("aaabb");
    w2.set("ubbcc");
    EXPECT_EQ(5, w1.editDist(w2));
    w1.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    EXPECT_EQ(57, w1.editDist(w2));
    w2.set("45678hgfjkbv678kjnbvcfd5678nbvgyuikmbv");
    w1.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67uiknbvfgy78uij");
    EXPECT_EQ(57, w1.editDist(w2));
    w1.set("kjhgfyuiokbgft&*GTijhbvft67ihGt7ijhgFT^&*IUYFGHJki76ytFCVJI&^TFVBJ");
    w2.set("98765rfghjkjhgfcvbji8765rfghjbvcde45678okjbgyuokjhgt678okjhgft67ui");
    EXPECT_EQ(63, w1.editDist(w2));
}

TEST(EditDistanceTest, Equal) {
    Word w1("a");
    Word w2("a");
    EXPECT_EQ(0, w1.editDist(w2));
    w1.set("aaabb");
    w2.set("aaabb");
    EXPECT_EQ(0, w1.editDist(w2));
    w1.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    EXPECT_EQ(0, w1.editDist(w2));
}


TEST(EditDistanceTest, Empty) { 
    Word w1("a");
    Word w2("");
    EXPECT_EQ(1, w1.editDist(w2));
    w1.set("");
    w2.set("aaabb");
    EXPECT_EQ(5, w1.editDist(w2));
    w1.set("");
    w2.set("kjhgyuiknbvghujkjhgy78i^%TGHJI*&^5trdvhi8765trfghi876tf");
    EXPECT_EQ(55, w1.editDist(w2));
}

