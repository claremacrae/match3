#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "board.hpp"
#include "mocks/irandom_mock.hpp"

namespace GT = testing;

namespace game {

std::ostream& operator<<(std::ostream& out, board& b) {
    out << "    ";
    for (int x = 0; x < b.cols_size_; ++x) {
        out << x << ". ";
    }
    out << std::endl;

    for (int y = 0; y < b.rows_size_; ++y) {
        out << y << ". ";
        for (int x = 0; x < b.cols_size_; ++x) {
            out << " " << b.get_grid_color(position(x, y)) << " ";
        }
        out << std::endl;
    }
    out << std::endl;

    return out;
}

namespace test {
namespace {

enum color_t
{
    none
  , black
  , blue
  , green
  , yellow
  , purple
};

void compare_boards(board& b1, board& b2) {
    std::cout << "b1:" << std::endl << b1;
    std::cout << "b2:" << std::endl << b2;

    for (const auto& pos : b1) {
        EXPECT_EQ(b1.get_grid_color(pos), b2.get_grid_color(pos));
    }

    for (const auto& pos : b2) {
        EXPECT_EQ(b1.get_grid_color(pos), b2.get_grid_color(pos));
    }
}

} // namespace

class board_test : public GT::Test
{
public:
    board_test()
        : irandom_mock_(new GT::StrictMock<mocks::irandom_mock>())
    { }

    std::shared_ptr<mocks::irandom_mock> irandom_mock_;
};

TEST_F(board_test, is_within_board) {
    //given
    board b(4, 4, 3, 5, irandom_mock_);

    //when and then
    EXPECT_TRUE(b.is_within_board(position(0, 0)));
    EXPECT_TRUE(b.is_within_board(position(1, 2)));
    EXPECT_TRUE(b.is_within_board(position(3, 3)));
    EXPECT_FALSE(b.is_within_board(position(4, 5)));
}

TEST_F(board_test, is_neighbor) {
    //given
    board b(4, 4, 3, 5, irandom_mock_);

    //when and then
    b.select(position(2, 2));
    EXPECT_TRUE(b.is_neighbor(position(1, 2)));
    EXPECT_TRUE(b.is_neighbor(position(2, 1)));
    EXPECT_TRUE(b.is_neighbor(position(2, 1)));
    EXPECT_TRUE(b.is_neighbor(position(3, 2)));
    EXPECT_TRUE(b.is_neighbor(position(2, 3)));
    EXPECT_FALSE(b.is_neighbor(position(2, 2)));
    EXPECT_FALSE(b.is_neighbor(position(1, 1)));
    EXPECT_FALSE(b.is_neighbor(position(3, 3)));
}

TEST_F(board_test, is_swap_winning_no) {
    //given
    board b(4, 4, 2, 5, irandom_mock_,
        {
            blue   , blue , black , purple
          , blue   , blue , green , purple
          , blue   , blue , black , purple
          , blue   , blue , green , purple
        }
    );

    b.select(position(2, 1));
    b.select(position(1, 1));

    //when
    b.swap(); std::cout << b;

    //then
    EXPECT_FALSE(b.is_swap_winning());
}

TEST_F(board_test, is_swap_winning_yes_simple) {
    //given
    board b(4, 4, 2, 5, irandom_mock_,
        {
            blue   , blue , black , blue
          , blue   , blue , blue  , blue
          , blue   , blue , black , blue
          , blue   , blue , blue  , blue
        }
    );

    b.select(position(2, 1));
    b.select(position(2, 2));

    //when
    b.swap(); std::cout << b;

    //then
    EXPECT_TRUE(b.is_swap_winning());
}

TEST_F(board_test, is_swap_winning_yes_complex) {
    //given
    board b(4, 4, 3, 5, irandom_mock_,
        {
            blue   , yellow , green  , purple
          , yellow , green  , blue   , black
          , purple , green  , yellow , purple
          , blue   , blue   , green  , black
        }
    );

    b.select(position(1, 3));
    b.select(position(2, 3));

    //when
    b.swap(); std::cout << b;

    //then
    EXPECT_TRUE(b.is_swap_winning());
}

TEST_F(board_test, matches) {
    //given
    board b(4, 4, 3, 5, irandom_mock_,
        {
            blue   , yellow , green  , purple
          , yellow , green  , blue   , black
          , purple , green  , yellow , purple
          , blue   , blue   , green  , black
        }
    );
    std::vector<position> m{position(1, 1), position(1, 2), position(1, 3)};

    b.select(position(1, 3));
    b.select(position(2, 3));
    b.swap(); std::cout << b;

    //expect
    EXPECT_CALL(*irandom_mock_, get_random_number(GT::_, GT::_)).WillRepeatedly(GT::Return(black));

    //when
    auto matches = b.matches();

    //then
    EXPECT_EQ(m.size(), matches.size());
    for (const auto& pos : m) {
        EXPECT_TRUE(matches.find(pos) != matches.end());
    }
}

TEST_F(board_test, scroll_down) {
    //given
    std::set<position> positions{ position(1, 1), position(1, 2), position(1, 3) };
    board b(4, 4, 3, 5, irandom_mock_,
        {
            blue   , yellow , green  , purple
          , yellow , green  , blue   , black
          , purple , green  , yellow , purple
          , blue   , blue   , green  , black
        }
    );

    board expected(4, 4, 3, 5, irandom_mock_,
        {
            blue   , none   , green  , purple
          , yellow , none   , blue   , black
          , purple , none   , yellow , purple
          , blue   , yellow , blue   , black
        }
    );

    b.select(position(1, 3));
    b.select(position(2, 3));
    b.swap(); std::cout << b;
    EXPECT_EQ(3u, b.matches().size());

    //when
    auto results = b.scroll_down();

    //then
    EXPECT_EQ(positions, results);
    compare_boards(b, expected);
}

TEST_F(board_test, new_randoms) {
    //given
    board b(4, 4, 3, 5, irandom_mock_,
        {
            none   , yellow , green  , purple
          , none   , green  , blue   , black
          , purple , green  , yellow , purple
          , blue   , blue   , green  , black
        }
    );
    std::vector<position> n{position(0, 0), position(0, 1)};

    //expect
    EXPECT_CALL(*irandom_mock_, get_random_number(GT::_, GT::_)).WillRepeatedly(GT::Return(black));

    //when
    auto new_randoms = b.new_randoms();

    //then
    EXPECT_EQ(n.size(), new_randoms.size());
    for (const auto& pos : n) {
        EXPECT_TRUE(new_randoms.find(pos) != new_randoms.end());
    }
}

} // namespace test
} // namespace game

