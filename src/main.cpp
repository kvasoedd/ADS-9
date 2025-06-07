// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <filesystem>

long long factorial(int n)
{
  long long res = 1;
  for (int i = 2; i <= n; ++i)
    res *= i;
  return res;
}

int main()
{
  using clk = std::chrono::high_resolution_clock;

  std::filesystem::path out_dir = "result";
  if (!std::filesystem::exists(out_dir))
  {
    std::filesystem::create_directory(out_dir);
  }

  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto p1 = getPerm1(tree, 1);
  auto p2 = getPerm2(tree, 2);
  auto all = getAllPerms(tree);

  std::cout << "getPerm1 #1: ";
  for (char c : p1)
    std::cout << c;
  std::cout << "\ngetPerm2 #2: ";
  for (char c : p2)
    std::cout << c;
  std::cout << "\nAll perms:\n";
  for (auto &perm : all)
  {
    for (char c : perm)
      std::cout << c;
    std::cout << '\n';
  }

  std::ofstream ofs("result/timings.csv");
  ofs << "n,getAll,get1,get2\n";

  std::mt19937_64 rng(12345);
  for (int n = 4; n <= 9; ++n)
  {
    std::vector<char> arr(n);
    for (int i = 0; i < n; ++i)
      arr[i] = 'A' + i;

    PMTree t(arr);

    int trials = 10;
    std::vector<double> t_all, t1, t2;
    std::uniform_int_distribution<long long> dist(1, factorial(n));

    for (int i = 0; i < trials; ++i)
    {
      int num = dist(rng);

      auto start = clk::now();
      getAllPerms(t);
      t_all.push_back(std::chrono::duration<double>(clk::now() - start).count());

      start = clk::now();
      getPerm1(t, num);
      t1.push_back(std::chrono::duration<double>(clk::now() - start).count());

      start = clk::now();
      getPerm2(t, num);
      t2.push_back(std::chrono::duration<double>(clk::now() - start).count());
    }

    auto avg = [&](const std::vector<double> &v)
    {
      double s = 0;
      for (auto x : v)
        s += x;
      return s / v.size();
    };

    ofs << n << "," << avg(t_all) << "," << avg(t1) << "," << avg(t2) << "\n";
    std::cout << "Completed n=" << n << "\n";
  }
  
  return 0;
}
