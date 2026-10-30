// 题目：982. 按位与为零的三元组（Triples with Bitwise AND Equal To Zero）
// 思路：先把所有 (x, y) 的与值出现次数统计进数组 cnt，再枚举 (与值, z)，若与值与 z 的与为 0，就把 cnt[与值] 全部累加。
// 时间复杂度：O(n^2 + V*n)，V 为元素最大值；空间复杂度：O(V)，计数数组大小。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    int countTriplets(vector<int>& nums) {  // nums 是输入数组
        int mx = ranges::max(nums);  // 元素最大值，决定计数数组的上界
        int cnt[mx + 1];  // cnt[s] 表示有多少对 (x, y) 的按位与结果为 s
        memset(cnt, 0, sizeof cnt);  // 计数数组全部清零
        for (int& x : nums) {  // 枚举第一个数 x
            for (int& y : nums) {  // 枚举第二个数 y
                cnt[x & y]++;  // 这一对的与值计数加一
            }  // 内层循环结束
        }  // 外层循环结束
        int ans = 0;  // ans 累计合法三元组个数
        for (int xy = 0; xy <= mx; ++xy) {  // 枚举所有可能出现的与值 xy
            for (int& z : nums) {  // 枚举第三个数 z
                if ((xy & z) == 0) {  // 三元组的按位与为 0
                    ans += cnt[xy];  // 与值为 xy 的所有 (x, y) 组合都满足要求，一次性累加计数
                }  // if 结束
            }  // z 循环结束
        }  // 与值循环结束
        return ans;  // 返回答案
    }  // 方法结束
};  // 类定义结束
