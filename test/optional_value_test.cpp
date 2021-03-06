#include <string>
#include <utility>

#include <gtest/gtest.h>

#include <optional/bad_optional_access.hpp>
#include <optional/none.hpp>
#include <optional/optional_value.hpp>

using opt::Optional;

TEST(OptionalValueTest, DefaultConstructor) {
    Optional<int> opt{};
    EXPECT_FALSE(opt);
}

TEST(OptionalValueTest, NoneTypeConstructor) {
    Optional<int> opt{opt::none};
    EXPECT_FALSE(opt);
}

TEST(OptionalValueTest, ConstLValueConstructor) {
    int i = 5;
    Optional<int> opt1{i};
    ASSERT_TRUE(opt1);
    EXPECT_EQ(5, *opt1);

    const int ii = -7;
    Optional<int> opt2{ii};
    ASSERT_TRUE(opt2);
    EXPECT_EQ(-7, *opt2);

    const char c = 'k';
    Optional<int> opt3{c};
    ASSERT_TRUE(opt3);
    EXPECT_EQ('k', *opt3);

    const char& c_r = c;
    Optional<int> opt4{c_r};
    ASSERT_TRUE(opt4);
    EXPECT_EQ('k', *opt4);
}

TEST(OptionalValueTest, RValueConstructor) {
    Optional<int> opt1{7};
    ASSERT_TRUE(opt1);
    EXPECT_EQ(7, *opt1);

    Optional<char> opt2{'k'};
    ASSERT_TRUE(opt2);
    EXPECT_EQ('k', *opt2);

    int i = -8;
    Optional<int> opt3{std::move(i)};
    ASSERT_TRUE(opt3);
    EXPECT_EQ(-8, *opt3);
}

TEST(OptionalValueTest, ConditionalConstructor) {
    const char c = 'k';
    const char& c_r = c;
    bool cond_t = true;
    bool cond_f = false;

    Optional<int> opt1{true, 7};
    ASSERT_TRUE(opt1);
    EXPECT_EQ(7, *opt1);

    Optional<int> opt2{false, 7};
    EXPECT_FALSE(opt2);

    Optional<char> opt3{cond_t, c};
    ASSERT_TRUE(opt3);
    EXPECT_EQ('k', *opt3);

    Optional<char> opt4{cond_f, c_r};
    EXPECT_FALSE(opt4);

    Optional<char> opt5{cond_t, c_r};
    EXPECT_TRUE(opt5);
    EXPECT_EQ('k', *opt5);
}

TEST(OptionalValueTest, CopyConstructor) {
    Optional<int> opt1{7};
    Optional<int> opt2{opt1};
    ASSERT_TRUE(opt2);
    EXPECT_EQ(7, *opt2);

    Optional<double> opt3{};
    Optional<double> opt4{opt3};
    EXPECT_FALSE(opt4);
}

TEST(OptionalValueTest, MoveConstructor) {
    Optional<int> opt1{9};
    Optional<int> opt2{std::move(opt1)};
    ASSERT_TRUE(opt2);
    EXPECT_EQ(9, *opt2);

    EXPECT_FALSE(opt1);

    Optional<int> opt3{Optional<int>{-5}};
    ASSERT_TRUE(opt3);
    EXPECT_EQ(-5, *opt3);

    Optional<int> opt4{Optional<int>{opt::none}};
    EXPECT_FALSE(opt4);

    Optional<double> opt5{};
    Optional<double> opt6{std::move(opt5)};
    EXPECT_FALSE(opt6);

    Optional<double> opt7{Optional<double>{}};
    EXPECT_FALSE(opt7);
}

TEST(OptionalValueTest, FromConvertibleTypeCopyConstructor) {
    Optional<int> opt_int{7};
    Optional<double> opt_dbl{opt_int};

    ASSERT_TRUE(opt_dbl);
    EXPECT_DOUBLE_EQ(7, *opt_dbl);

    Optional<const char*> opt_c_str{"Hello"};
    Optional<std::string> opt_string{opt_c_str};

    ASSERT_TRUE(opt_string);
    EXPECT_EQ("Hello", *opt_string);

    Optional<double> opt_dbl2{};
    Optional<int> opt_int2{opt_dbl2};
    EXPECT_FALSE(opt_int2);
}

TEST(OptionalValueTest, FromConvertibleTypeMoveConstructor) {
    Optional<int> opt_int{2};
    Optional<double> opt_dbl{std::move(opt_int)};
    ASSERT_TRUE(opt_dbl);
    EXPECT_DOUBLE_EQ(2, *opt_dbl);

    EXPECT_FALSE(opt_int);

    Optional<double> opt_dbl2{};
    Optional<int> opt_int2{opt_dbl2};
    EXPECT_FALSE(opt_int2);

    Optional<const char*> opt_c_str{"Hello"};
    Optional<std::string> opt_string{std::move(opt_c_str)};

    ASSERT_TRUE(opt_string);
    EXPECT_EQ("Hello", *opt_string);
    EXPECT_FALSE(opt_c_str);
}

TEST(OptionalValueTest, NoneAssignementOperator) {
    Optional<int> opt{8};
    ASSERT_TRUE(opt);
    EXPECT_EQ(8, *opt);

    opt = opt::none;
    EXPECT_FALSE(opt);
}

TEST(OptionalValueTest, LValueTAssignmentOperator) {
    Optional<int> opt{-77};
    int i = 45;
    opt = i;
    ASSERT_TRUE(opt);
    EXPECT_EQ(45, *opt);

    const int c_i = 99;
    opt = c_i;
    ASSERT_TRUE(opt);
    EXPECT_EQ(99, *opt);
}

TEST(OptionalValueTest, RValueTAssignmentOperator) {
    Optional<int> opt1{};
    opt1 = 99;
    ASSERT_TRUE(opt1);
    EXPECT_EQ(99, *opt1);

    Optional<int> opt2{-77};
    opt2 = 88;
    ASSERT_TRUE(opt2);
    EXPECT_EQ(88, *opt2);
}

TEST(OptionalValueTest, CopyAssignmentOperator) {
    Optional<int> opt1{99};
    Optional<int> opt2{7};

    opt1 = opt2;

    ASSERT_TRUE(opt1);
    EXPECT_EQ(7, *opt1);

    Optional<int> opt3{0};
    EXPECT_EQ(0, *(opt2 = opt3));

    Optional<int> opt_empty{};
    opt1 = opt_empty;

    EXPECT_FALSE(opt1);
}

TEST(OptionalValueTest, MoveAssignmentOperator) {
    Optional<int> opt1{5};
    Optional<int> opt2{};

    opt2 = std::move(opt1);

    EXPECT_FALSE(opt1);
    ASSERT_TRUE(opt2);
    EXPECT_EQ(5, *opt2);

    Optional<int> opt3{};
    opt3 = Optional<int>{9};

    ASSERT_TRUE(opt3);
    EXPECT_EQ(9, *opt3);
}

TEST(OptionalValueTest, ConversionCopyAssignmentConstructor) {
    Optional<int> opt_int{7};
    Optional<double> opt_dbl{10.0};

    opt_dbl = opt_int;

    ASSERT_TRUE(opt_dbl);
    EXPECT_DOUBLE_EQ(7, *opt_dbl);
    ASSERT_TRUE(opt_int);
    EXPECT_EQ(7, *opt_int);

    Optional<const char*> opt_c_str{"Hello"};
    Optional<std::string> opt_string{"World!"};

    opt_string = opt_c_str;

    ASSERT_TRUE(opt_string);
    EXPECT_EQ("Hello", *opt_string);
    ASSERT_TRUE(opt_c_str);
    EXPECT_EQ("Hello", *opt_c_str);

    Optional<long int> opt_long{4321};
    EXPECT_EQ(7, *(opt_long = opt_int));

    Optional<int> opt_empty{};
    Optional<double> opt_dbl2{8};

    opt_dbl2 = opt_empty;

    EXPECT_FALSE(opt_dbl2);
}

TEST(OptionalValueTest, ConversionMoveAssignmentOperator) {
    Optional<int> opt_int{6};
    Optional<double> opt_dbl{8.4};

    opt_dbl = std::move(opt_int);

    ASSERT_TRUE(opt_dbl);
    EXPECT_DOUBLE_EQ(6, *opt_dbl);
    EXPECT_FALSE(opt_int);

    opt_dbl = Optional<int>{99};

    ASSERT_TRUE(opt_dbl);
    EXPECT_DOUBLE_EQ(99, *opt_dbl);

    opt_dbl = Optional<int>{};

    EXPECT_FALSE(opt_dbl);
}

TEST(OptionalValueTest, Emplace) {
    Optional<int> opt1{};
    opt1.emplace(6);

    ASSERT_TRUE(opt1);
    EXPECT_EQ(6, *opt1);

    Optional<std::string> opt2{};
    opt2.emplace(3, 'h');

    ASSERT_TRUE(opt2);
    EXPECT_EQ("hhh", *opt2);

    opt2.emplace(std::string{"Hello!"});

    ASSERT_TRUE(opt2);
    EXPECT_EQ("Hello!", *opt2);

    opt2.emplace();
    ASSERT_TRUE(opt2);
    EXPECT_EQ("", *opt2);
}

TEST(OptionalValueTest, ConstGet) {
    const Optional<int> opt{9};
    ASSERT_TRUE(opt);
    EXPECT_EQ(9, opt.get());
}

TEST(OptionalValueTest, Get) {
    Optional<int> opt{7};
    ASSERT_TRUE(opt);
    EXPECT_EQ(7, opt.get());

    opt.get() = 9;
    ASSERT_TRUE(opt);
    EXPECT_EQ(9, opt.get());
}

TEST(OptionalValueTest, ConstArrowOperator) {
    const Optional<std::string> opt{"Hello, World!"};
    ASSERT_TRUE(opt);
    EXPECT_EQ(13, opt->size());
}

TEST(OptionalValueTest, ArrowOperator) {
    Optional<std::string> opt{"Hello"};
    ASSERT_TRUE(opt);
    EXPECT_EQ(5, opt->size());
    opt->append(", World!");
    EXPECT_EQ("Hello, World!", *opt);
}

TEST(OptionalValueTest, ConstLValueDereferenceOperator) {
    const Optional<const int> opt_int{88};
    ASSERT_TRUE(opt_int);
    EXPECT_EQ(88, *opt_int);

    const Optional<std::string> opt_string{"Hello!"};
    ASSERT_TRUE(opt_string);
    EXPECT_EQ(6, (*opt_string).size());
}

TEST(OptionalValueTest, LValueDereferenceOperator) {
    Optional<std::string> opt_string{"Hello"};
    ASSERT_TRUE(opt_string);
    EXPECT_EQ(5, (*opt_string).size());

    (*opt_string).append(", World!");
    ASSERT_TRUE(opt_string);
    EXPECT_EQ("Hello, World!", *opt_string);
}

TEST(OptionalValueTest, RValueDereferenceOperator) {
    EXPECT_EQ(6, (*Optional<std::string>{"Hello!"}).size());
    EXPECT_EQ(77, *Optional<int>{77});

    Optional<std::string> opt{"Hello, World!"};
    ASSERT_TRUE(opt);
    EXPECT_EQ("Hello, World!", *std::move(opt));
}

TEST(OptionalValueTest, ConstLValueValueMethod) {
    const Optional<int> opt1{};
    EXPECT_THROW(opt1.value(), opt::Bad_optional_access);

    const Optional<int> opt2{8};
    ASSERT_TRUE(opt2);
    EXPECT_NO_THROW(opt2.value());
    EXPECT_EQ(8, opt2.value());
}

TEST(OptionalValueTest, LValueValueMethod) {
    Optional<int> opt1{};
    EXPECT_THROW(opt1.value(), opt::Bad_optional_access);

    Optional<int> opt2{8};
    ASSERT_TRUE(opt2);
    EXPECT_NO_THROW(opt2.value());
    EXPECT_EQ(8, opt2.value());

    Optional<std::string> opt_string{"Hello"};
    opt_string.value().append(", World!");
    ASSERT_TRUE(opt_string);
    EXPECT_EQ("Hello, World!", *opt_string);
}

TEST(OptionalValueTest, RValueValueMethod) {
    Optional<int> opt1{};
    EXPECT_THROW(std::move(opt1).value(), opt::Bad_optional_access);
    EXPECT_FALSE(opt1);

    Optional<int> opt2{8};
    ASSERT_TRUE(opt2);
    EXPECT_NO_THROW(std::move(opt2).value());

    Optional<int> opt3{10};
    ASSERT_TRUE(opt3);
    EXPECT_EQ(10, std::move(opt3).value());

    EXPECT_EQ(6, (Optional<int>{6}).value());
    EXPECT_NO_THROW((Optional<int>{6}).value());
    EXPECT_THROW((Optional<int>{}).value(), opt::Bad_optional_access);
}

TEST(OptionalValueTest, ConstLValueValueOr) {
    Optional<int> opt{8};
    ASSERT_TRUE(opt);
    EXPECT_DOUBLE_EQ(8, opt.value_or(7.2));

    Optional<int> opt_empty{};
    EXPECT_FALSE(opt_empty);
    int i = 32;
    EXPECT_EQ(i, opt_empty.value_or(i));
    double d = 6.3;
    EXPECT_EQ(6, opt_empty.value_or(d));
}

TEST(OptionalValueTest, RValueValueOr) {
    Optional<int> opt1{};
    double d = 9.3;
    EXPECT_EQ(9, std::move(opt1).value_or(d));
    EXPECT_FALSE(opt1);

    Optional<int> opt2{8};
    ASSERT_TRUE(opt2);
    EXPECT_EQ(8, std::move(opt2).value_or(9.3));

    Optional<int> opt3{10};
    ASSERT_TRUE(opt3);
    EXPECT_EQ(10, std::move(opt3).value_or(843));

    EXPECT_EQ(6, (Optional<int>{6}).value_or(99));
    EXPECT_EQ(99, (Optional<int>{}).value_or(99));
}

double f() {
    return 7.7;
}

TEST(OptionalValueTest, ConstLValueValueOrEval) {
    Optional<int> opt{5};
    ASSERT_TRUE(opt);
    EXPECT_EQ(5, opt.value_or_eval([]() { return 8; }));

    opt = opt::none;
    EXPECT_FALSE(opt);
    EXPECT_EQ(8, opt.value_or_eval([]() { return 8; }));

    EXPECT_EQ(7, opt.value_or_eval(f));
    opt = -4;
    EXPECT_EQ(-4, opt.value_or_eval(f));
}

TEST(OptionalValueTest, RValueValueOrEval) {
    EXPECT_EQ(3, (Optional<int>{3}).value_or_eval([]() { return 8; }));

    Optional<int> opt1{};
    EXPECT_EQ(2, opt1.value_or_eval([]() { return 2; }));
    EXPECT_FALSE(opt1);

    Optional<int> opt2{88};
    EXPECT_EQ(88, std::move(opt2).value_or_eval([]() { return 3; }));
}

TEST(OptionalValueTest, ConstGetPtr) {
    const Optional<std::string> opt{"Hello!"};
    EXPECT_EQ("Hello!", *(opt.get_ptr()));
}

TEST(OptionalValueTest, GetPtr) {
    Optional<std::string> opt{"Hello"};
    EXPECT_EQ("Hello", *(opt.get_ptr()));
    opt.get_ptr()->append(", World!");
    EXPECT_EQ("Hello, World!", *(opt.get_ptr()));
}
