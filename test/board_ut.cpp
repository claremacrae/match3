#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include "board.hpp"
#include "mocks/irandom_mock.hpp"

namespace GT = testing;

namespace game {
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

std::ostream& operator<<(std::ostream& out, board& b) {
    out << "    ";
    for (int x = 0; x < b.get_cols(); ++x) {
        out << x << ". ";
    }
    out << std::endl;

    for (int y = 0; y < b.get_rows(); ++y) {
        out << y << ". ";
        for (int x = 0; x < b.get_cols(); ++x) {
            out << " " << b.get_grid_color(position(x, y)) << " ";
        }
        out << std::endl;
    }
    out << std::endl;

    return out;
}

void fill_board(board& board, std::vector<color_t> colors) {
    int i = 0;
    for (int y = 0; y < board.get_rows(); ++y) {
        for (int x = 0; x < board.get_cols(); ++x) {
            board.set(position(x, y), colors[i++]);
        }
    }

    std::cout << board;
}

void compare_boards(board& b1, board& b2) {
    std::cout << "b1:" << std::endl << b1;
    std::cout << "b2:" << std::endl << b2;

    EXPECT_EQ(b1.get_rows(), b2.get_rows());
    EXPECT_EQ(b1.get_cols(), b2.get_cols());

    for (int y = 0; y < b1.get_rows(); ++y) {
        for (int x = 0; x < b1.get_cols(); ++x) {
            EXPECT_EQ(b1.get_grid_color(position(x, y)), b2.get_grid_color(position(x, y)));
        }
    }
}

} // namespace

class board_test : public GT::Test
{
public:
    board_test()
        : irandom_mock_(new GT::StrictMock<mocks::irandom_mock>())
    { }

    boost::shared_ptr<mocks::irandom_mock> irandom_mock_;
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
    board b(4, 4, 2, 5, irandom_mock_);
    fill_board(b,
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
    board b(4, 4, 2, 5, irandom_mock_);
    fill_board(b,
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
    board b(4, 4, 3, 5, irandom_mock_);
    fill_board(b,
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
    //expect
    EXPECT_CALL(*irandom_mock_, get_random_number(GT::_, GT::_)).WillRepeatedly(GT::Return(black));

    //given
    board b(4, 4, 3, 5, irandom_mock_);
    std::vector<position> m{position(1, 1), position(1, 2), position(1, 3)};
    fill_board(b,
        {
            blue   , yellow , green  , purple
          , yellow , green  , blue   , black
          , purple , green  , yellow , purple
          , blue   , blue   , green  , black
        }
    );

    b.select(position(1, 3));
    b.select(position(2, 3));
    b.swap(); std::cout << b;

    //when
    auto matches = b.matches();

    //then
    EXPECT_EQ(m.size(), matches.size());
    for (std::size_t i = 0; i < m.size(); ++i) {
        EXPECT_TRUE(matches.find(m[i]) != matches.end());
    }
}

TEST_F(board_test, scroll_down) {
    //expect
    EXPECT_CALL(*irandom_mock_, get_random_number(GT::_, GT::_)).WillRepeatedly(GT::Return(black));

    //given
    board b(4, 4, 3, 5, irandom_mock_);

    fill_board(b,
        {
            blue   , yellow , green  , purple
          , yellow , green  , blue   , black
          , purple , green  , yellow , purple
          , blue   , blue   , green  , black
        }
    );

    board expected(4, 4, 3, 5, irandom_mock_);
    fill_board(expected,
        {
            blue   , black   , green  , purple
          , yellow , black   , blue   , black
          , purple , black   , yellow , purple
          , blue   , yellow  , blue   , black
        }
    );

    b.select(position(1, 3));
    b.select(position(2, 3));
    b.swap(); std::cout << b;
    EXPECT_EQ(3u, b.matches().size());

    //when
    b.scroll_down();

    //then
    compare_boards(b, expected);
}

} // namespace test
} // namespace game

