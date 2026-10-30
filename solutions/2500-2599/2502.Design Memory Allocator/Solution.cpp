// 题目：2502. 设计内存分配器（Design Memory Allocator）
// 思路：用长度 n 的数组模拟内存，0 表示空闲、正数表示占用它的 mID；allocate 顺序扫描找连续 size 个空闲并整段标记，freeMemory 全表清零该 mID。
// 时间复杂度：allocate 与 freeMemory 均为 O(n)；空间复杂度：O(n)，保存 n 个内存单元。
class Allocator {  // LeetCode 约定的题解类 Allocator
public:  // 构造函数与成员方法对外可见
    vector<int> m;  // m：长度 n 的内存数组，0 表示空闲，正数表示占用它的 mID

    Allocator(int n) {  // 构造函数：n 为内存单元总数
        m = vector<int>(n, 0);  // 初始化 n 个空闲单元（全部置 0）
    }  // 构造函数结束

    int allocate(int size, int mID) {  // 分配 size 个连续单元给 mID，返回起始下标；失败返回 -1
        int cnt = 0;  // cnt：当前已经连续遇到的空闲单元个数
        for (int i = 0; i < m.size(); ++i) {  // 从左到右扫描整个内存数组
            if (m[i] > 0) {  // 遇到被占用的单元
                cnt = 0;  // 连续空闲被中断，计数器清零
            } else if (++cnt == size) {  // 否则空闲单元数加一；刚好凑满 size 个时开始分配
                fill(m.begin() + i - size + 1, m.begin() + i + 1, mID);  // 把 [i - size + 1, i] 这段连续空闲单元整段标记为 mID
                return i - size + 1;  // 返回这段内存的起始下标
            }  // if / else-if 分支结束
        }  // 扫描结束仍未找到足够长的连续空闲
        return -1;  // 分配失败，返回 -1
    }  // allocate 方法结束

    int freeMemory(int mID) {  // 释放所有属于 mID 的内存，返回释放的单元数
        int ans = 0;  // ans：已释放的单元个数
        for (int i = 0; i < m.size(); ++i) {  // 扫描整个内存数组
            if (m[i] == mID) {  // 找到属于 mID 的单元
                m[i] = 0;  // 把它重新标记为空闲
                ++ans;  // 释放计数加一
            }  // 分支结束
        }  // 扫描结束
        return ans;  // 返回释放的总单元数
    }  // freeMemory 方法结束
};  // 类定义结束

// 下面这段是 LeetCode 给出的调用示例注释，原样保留以便对照
/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->freeMemory(mID);
 */
