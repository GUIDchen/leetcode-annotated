// 题目：2166. 设计位集（Design Bitset）
// 思路：同时维护正串 a 与取反串 b，并记录 a 中 1 的个数 cnt；flip 时只交换两串并把 cnt 换成 size - cnt，避免逐位取反。
// 时间复杂度：除 toString 为 O(n) 外各操作均 O(1)；空间复杂度：O(n)，两条等长字符串。
class Bitset {  // 位集类，需实现 fix/unfix/flip/all/one/count/toString
public:  // 对外提供的接口区
    string a, b;  // a：当前位集的正向表示；b：a 逐位取反后的表示，省掉 flip 的 O(n) 开销
    int cnt = 0;  // cnt：a 中 '1' 的个数，all、one、count 都靠它 O(1) 回答

    Bitset(int size) {  // 构造：初始化长度为 size 的位集
        a = string(size, '0');  // 正向表示初始全为 0
        b = string(size, '1');  // 取反表示初始全为 1
    }  // 构造函数结束

    void fix(int idx) {  // 把第 idx 位置为 1
        if (a[idx] == '0') a[idx] = '1', ++cnt;  // 原来就是 '0' 时才需要更新计数，否则重复累加会算错
        b[idx] = '0';  // 同步维护取反串的对应位为 '0'
    }  // fix 结束

    void unfix(int idx) {  // 把第 idx 位置为 0
        if (a[idx] == '1') a[idx] = '0', --cnt;  // 原来是 '1' 时才需要减少计数，避免重复相减
        b[idx] = '1';  // 同步维护取反串的对应位为 '1'
    }  // unfix 结束

    void flip() {  // 整体翻转所有位
        swap(a, b);  // 交换正反两串即等价于逐位取反，省掉 O(n) 遍历
        cnt = a.size() - cnt;  // 翻转后 1 的个数变成总长度减去原来的 1 的个数
    }  // flip 结束

    bool all() {  // 判断是否全为 1
        return cnt == a.size();  // 1 的个数等于总长度就说明全为 1
    }  // all 结束

    bool one() {  // 判断是否至少有一个 1
        return cnt > 0;  // 计数大于 0 即存在 1
    }  // one 结束

    int count() {  // 返回当前 1 的个数
        return cnt;  // 直接返回一直维护着的计数器
    }  // count 结束

    string toString() {  // 把当前位集转成字符串
        return a;  // 直接返回正向表示，字符顺序与下标一致
    }  // toString 结束
};  // 类定义结束

// 下面这段是 LeetCode 判题器要求的对象创建与调用示例注释，原样保留
/**
 * Your Bitset object will be instantiated and called as such:
 * Bitset* obj = new Bitset(size);
 * obj->fix(idx);
 * obj->unfix(idx);
 * obj->flip();
 * bool param_4 = obj->all();
 * bool param_5 = obj->one();
 * int param_6 = obj->count();
 * string param_7 = obj->toString();
 */