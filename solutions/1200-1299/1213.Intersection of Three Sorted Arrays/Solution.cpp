// 题目：1213. 三个有序数组的交集（Intersection of Three Sorted Arrays）
// 思路：值域很小（0..2000），用一个计数桶累加三个数组的出现次数，某个值被计到 3 就说明它同时出现在三个数组里。
// 时间复杂度：O(n1 + n2 + n3)，三个数组各扫一次；空间复杂度：O(V)，V 为值域大小（这里固定 2001 个桶）。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    vector<int> arraysIntersection(vector<int>& arr1, vector<int>& arr2, vector<int>& arr3) {  // arr1、arr2、arr3：三个升序数组；返回同时出现在三者中的元素
        vector<int> ans;  // 保存交集结果
        int cnt[2001]{};  // 值域 0..2000 的计数桶，花括号初始化使得全部为 0
        for (int x : arr1) {  // 统计 arr1 中每个值的出现次数
            ++cnt[x];  // 对应桶计数加一
        }  // arr1 统计结束
        for (int x : arr2) {  // 继续累加 arr2 的出现次数
            ++cnt[x];  // 对应桶计数加一
        }  // arr2 统计结束
        for (int x : arr3) {  // 扫 arr3，边累加边判断是否已被三个数组覆盖
            if (++cnt[x] == 3) {  // 累加后正好等于 3，说明三个数组都含有 x
                ans.push_back(x);  // 把 x 加入结果；arr3 升序，故结果天然有序
            }  // 计数判断结束
        }  // arr3 扫描结束
        return ans;  // 返回有序的交集数组
    }  // arraysIntersection 方法结束
};  // 题解类定义结束