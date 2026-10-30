// 3940. 限制有序数组中的元素出现次数 / Limit Occurrences in Sorted Array
// 核心思路：数组有序，用快慢指针原地覆盖，统计当前连续相同元素已保留的个数，不超过 k 个就写回。
// 复杂度：时间 O(n)，空间 O(1)。
class Solution {  // 题解类定义
public:  // 公开接口
    vector<int> limitOccurrences(vector<int>& nums, int k) {  // 主函数：每个元素最多保留 k 次
        int n = nums.size();  // 数组长度
        int cnt = 1, l = 1;  // cnt 为当前元素已保留次数，l 为写指针

        for (int r = 1; r < n; r++) {  // r 为读指针，从第二个元素开始扫描
            if (nums[r] != nums[r - 1]) {  // 遇到与上一个不同的新元素
                cnt = 1;  // 新元素的保留计数重置为 1
            } else {  // 仍是同一个元素
                cnt++;  // 保留计数累加
            }  // if-else 分支结束

            if (cnt <= k) {  // 尚未超过允许的出现次数
                nums[l] = nums[r];  // 把该元素原地写到写指针位置
                l++;  // 写指针后移
            }  // if 分支结束
        }  // 扫描循环结束

        nums.resize(l);  // 截断到实际保留的元素个数
        return nums;  // 返回结果数组
    }  // limitOccurrences 函数结束
};  // 类定义结束