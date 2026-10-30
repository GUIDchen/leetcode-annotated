// 题目：3890. 可由多种立方和构造的整数（Integers With Multiple Sum of Two Cubes）
// 思路：预处理所有 a³+b³ ≤ 1e9 的组合并计数，出现次数大于 1 的和即为“好数”；排序后每次查询二分出 ≤ n 的前缀。
// 时间复杂度：预处理 O(1000²) 约 1e6，单次查询 O(log |GOOD|)；空间复杂度：O(1000²) 用于哈希表计数。
vector<int> GOOD;  // 全局有序表，存放所有“可由多种立方和构造”的整数

auto init = [] {  // 立即执行的 lambda，用于完成一次性的预处理
    const int LIMIT = 1e9;  // 立方和的上界

    unordered_map<int, int> cnt;  // 哈希表：立方和 → 能被多少对 (a, b) 表示
    vector<int> cubes(1001);  // 预存 0..1000 的立方值

    for (int i = 0; i <= 1000; ++i) {  // 预先算好每个数的立方
        cubes[i] = i * i * i;  // cubes[i] = i³
    }  // 结束立方预计算

    for (int a = 1; a <= 1000; ++a) {  // 枚举较小的那一项 a
        for (int b = a; b <= 1000; ++b) {  // 强制 b ≥ a，避免 (a,b) 与 (b,a) 被重复计数
            int x = cubes[a] + cubes[b];  // 两数立方和
            if (x > LIMIT) break;  // b 继续增大只会更大，可以直接跳出内层循环
            cnt[x]++;  // 该立方和的表示方式数加 1
        }  // 结束内层循环
    }  // 结束外层循环

    for (auto& [x, v] : cnt) {  // 遍历所有出现过的立方和
        if (v > 1) {  // 表示方式超过一种才是好数
            GOOD.push_back(x);  // 收集进全局表
        }  // 结束判断
    }  // 结束遍历

    sort(GOOD.begin(), GOOD.end());  // 排序，为后续二分查询做准备

    return 0;  // lambda 需要返回值，随便返回 0
}();  // 调用 lambda，完成静态初始化

class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> findGoodIntegers(int n) {  // n：查询上界
        int idx = upper_bound(GOOD.begin(), GOOD.end(), n) - GOOD.begin();  // 二分出 ≤ n 的好数个数（upper_bound 返回第一个大于 n 的位置）
        return vector<int>(GOOD.begin(), GOOD.begin() + idx);  // 取前 idx 个元素作为答案
    }  // 结束方法
};  // 结束类
