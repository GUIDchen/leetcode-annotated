// 题目：2007. 从双倍数组中还原原数组（Find Original Array From Doubled Array）
// 思路：升序排序后最小值一定属于原数组，于是用计数数组从小到大贪心配对：取出 x 作为原数组元素，同时消耗一个 2x；任何一步配对失败就说明无法还原。
// 时间复杂度：O(n log n)，排序占主导，贪心扫描是 O(n + max(changed))；空间复杂度：O(max(changed))，计数数组。
class Solution {  // LeetCode 约定的题解类
public:
    vector<int> findOriginalArray(vector<int>& changed) {  // changed 是双倍数组；返回还原出的原数组，无法还原时返回空数组
        sort(changed.begin(), changed.end());  // 升序排序：排序不改变元素集合，而排序后的最小值必然属于原数组，从这里开始贪心配对
        vector<int> cnt(changed.back() + 1);  // 计数数组，大小为最大值 + 1；cnt[x] 表示值 x 还剩下几个没被配对
        for (int x : changed) {  // 遍历数组统计每个值的出现次数
            ++cnt[x];  // 值 x 的剩余个数加一
        }  // 统计结束
        vector<int> ans;  // ans 收集原数组的元素
        for (int x : changed) {  // 按升序遍历，保证先处理较小的值
            if (cnt[x] == 0) {  // 该值已经被前面的元素配对消耗完
                continue;  // 这一份已经用掉，跳过
            }  // if 结束
            --cnt[x];  // 把 x 分配给原数组，剩余个数减一
            int y = x << 1;  // 与原数组中 x 配对的那个元素应当是 2x
            if (y >= cnt.size() || cnt[y] <= 0) {  // 2x 越界或已经没有剩余，说明无法配对成功
                return {};  // 无法还原，返回空数组
            }  // if 结束
            --cnt[y];  // 配对成功，2x 的剩余个数也减一
            ans.push_back(x);  // x 属于原数组，收集起来
        }  // for 循环结束
        return ans;  // 全部元素都配对成功，返回原数组
    }  // findOriginalArray 方法结束
};  // Solution 类结束