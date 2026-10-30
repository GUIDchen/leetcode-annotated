// 题目：277. 搜寻名人（Find the Celebrity）
// 思路：第一轮 O(n) 用「候选人认识谁就换谁」淘汰，唯一留下的人可能是名人；第二轮再 O(n) 验证他不认识任何人且被所有人认识，否则返回 -1。
// 时间复杂度：O(n)，两轮线性扫描；空间复杂度：O(1)，只用几个变量。
/* The knows API is defined for you.
      bool knows(int a, int b); */  // knows(a, b) 返回 a 是否认识 b，由判题器提供实现

class Solution {  // LeetCode 约定的题解类
public:  // 对外提供 findCelebrity 方法
    int findCelebrity(int n) {  // n：人数，编号 0..n-1；返回名人编号，没有则返回 -1
        int ans = 0;  // 候选名人先假设为 0 号
        for (int i = 1; i < n; ++i) {  // 第一轮：一次询问淘汰一个不可能是名人的人
            if (knows(ans, i)) {  // ans 认识 i，说明 ans 不是名人，候选换成 i
                ans = i;  // 更新候选（i 也可能不是，留到第二轮验证）
            }
        }
        for (int i = 0; i < n; ++i) {  // 第二轮：验证候选是否满足名人定义
            if (ans != i) {  // 跳过自己和自己比较
                if (knows(ans, i) || !knows(i, ans)) {  // 名人必须不认识任何人，且被所有人认识；任一不满足就是没有名人
                    return -1;  // 返回 -1 表示不存在名人
                }
            }
        }
        return ans;  // 验证通过，返回名人编号
    }
};