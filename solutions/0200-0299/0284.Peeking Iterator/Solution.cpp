// 题目：284. 窥视迭代器（Peeking Iterator）
// 思路：用 hasPeeked 标记是否已经预取过，peek 时若未预取就调用基类 next 并缓存；next 优先返回缓存值，hasNext 也要把缓存算作还有元素。
// 时间复杂度：均摊 O(1) 每次操作；空间复杂度：O(1)，只多存一个缓存元素。
/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {  // 继承题目给定的 Iterator 接口
public:  // 对外提供 peek / next / hasNext
    PeekingIterator(const vector<int>& nums)  // 构造函数：只接管基类迭代器，不保存 nums 本身
        : Iterator(nums) {  // 把 nums 交给基类 Iterator 构造
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        hasPeeked = false;  // 初始没有预取过的元素
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek() {  // 查看下一个元素但不前进迭代器
        if (!hasPeeked) {  // 还没预取过，就先真正取一个出来
            peekedElement = Iterator::next();  // 调用基类 next 真正前进一步并缓存结果
            hasPeeked = true;  // 标记已预取，后续重复 peek 直接返回缓存
        }
        return peekedElement;  // 返回缓存的元素
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next() {  // 取下一个元素并真正前进
        if (!hasPeeked) return Iterator::next();  // 没有预取：等价于基类的 next；有预取：直接吐出缓存
        hasPeeked = false;  // 缓存已被消费，清除标记
        return peekedElement;  // 返回刚才缓存的元素
    }

    bool hasNext() const {  // 是否还有元素；const 成员函数不修改对象状态
        return hasPeeked || Iterator::hasNext();  // 缓存里还有元素，或者基类仍有剩余元素
    }

private:  // 内部状态（题目允许在此新增成员）
    bool hasPeeked;  // 是否已经预取过元素
    int peekedElement;  // 预取出来的元素缓存
};