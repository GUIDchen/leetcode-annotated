// 题目：2558. 从数量最多的堆取走礼物（Take Gifts From the Richest Pile）
// 思路：用大根堆维护每堆礼物数，每次把堆顶（最大堆）开平方取整后重新入堆，重复 k 次，最后求和。
// 时间复杂度：O(n + k log n)，建堆 O(n)，每次取堆顶加回堆 O(log n)；空间复杂度：O(1)，堆是原地构建的。
class Solution {  // LeetCode 约定的题解类
public:  // 题解方法对外可见
    long long pickGifts(vector<int>& gifts, int k) {  // gifts 是每堆礼物的数量，k 是操作次数；返回值用 long long 防止累加溢出
        make_heap(gifts.begin(), gifts.end());  // 原地建大根堆，堆顶就是当前数量最多的一堆
        while (k--) {  // 重复 k 次，每次对当前最多的一堆开平方
            pop_heap(gifts.begin(), gifts.end());  // 把堆顶移到末尾，此时 gifts.back() 就是最大值
            gifts.back() = sqrt(gifts.back());  // 对这堆开平方：sqrt 返回 double，赋给 int 时截断小数部分
            push_heap(gifts.begin(), gifts.end());  // 把更新后的这堆重新压回堆，恢复堆性质
        }  // k 次操作结束
        return accumulate(gifts.begin(), gifts.end(), 0LL);  // 求和；初始值 0LL 让累加结果是 long long
    }  // pickGifts 方法结束
};  // Solution 类定义结束