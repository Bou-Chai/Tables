

template <typename T>
class Cell : public CellBase {
public:
    T getData() {
        return data;
    }

    void setData(T data) {
        this->data = data;
    }

private:
    T data;
};
