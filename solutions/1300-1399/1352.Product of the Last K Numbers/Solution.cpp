// 题目：1352. 最后 K 个数的乘积（Product of the Last K Numbers）
// 思路：维护一份「以最后一次清零为起点」的前缀乘积数组，查询最后 k 个数的乘积时用两次前缀乘积相除还原区间积；遇到 0 就把前缀数组重置为 [1]。
// 时间复杂度：add 与 getProduct 均摊都是 O(1)；空间复杂度：O(n)，n 为两次 0 之间加入的元素个数。
class ProductOfNumbers {  // 设计题：用一个类同时维护数据流和前缀乘积
public:  // 构造与两个接口对外可见
    ProductOfNumbers() {  // 构造函数：初始化内部的前缀乘积数组
        s.push_back(1);  // 先放一个哨兵 1，使得第一个元素也能用「除以哨兵」的方式取区间乘积
    }

    void add(int num) {  // 向数据流末尾追加一个数 num
        if (num == 0) {  // 一旦遇到 0，任何跨过这个 0 的区间乘积都会变成 0，历史前缀全部失效
            s.clear();  // 清空历史前缀乘积，重新开始统计
            s.push_back(1);  // 重新放入哨兵 1 作为新的起点
            return;  // 本次 add 处理完毕，直接返回
        }
        s.push_back(s.back() * num);  // 非 0：前缀乘积继续向后累乘，s[i] = a[0] * a[1] * ... * a[i]
    }

    int getProduct(int k) {  // 查询最后 k 个数的乘积
        int n = s.size();  // n 为前缀乘积数组的长度（其中含一个哨兵）
        return n <= k ? 0 : s.back() / s[n - k - 1];  // 元素不足 k 个说明中间出现过 0（此时前缀数组被重置过），应返回 0；否则用 s[末尾] / s[n-k-1] 得到区间积
    }

private:  // 私有部分：只允许本类访问
    vector<int> s;  // s[0] 是哨兵 1，s[i] 是加入的第 i 个数的前缀乘积
};

/**  // 下面是 LeetCode 判题器给出的调用示例，属于模板注释，原样保留
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */