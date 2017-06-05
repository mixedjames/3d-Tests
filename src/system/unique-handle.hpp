#pragma once

namespace james {

  template<typename T, typename Completer, Completer complete, T nullV = T()>
  struct unique_handle {
    static const T null_value = nullV;
    typedef typename T type;
    typedef typename Completer completer_type;

    unique_handle() : t_(null_value) {}
    unique_handle(std::nullptr_t) : t_(null_value) {}
    explicit unique_handle(T t) : t_(t) {}
    unique_handle(unique_handle& src) : t_(src.t_) { src.t_ = null_value; }
    
    ~unique_handle() { if (t_ != null_value) { complete(t_); } }

    unique_handle& operator =(unique_handle& src) noexcept {
      unique_handle tmp(src);
      swap(tmp);
      return *this;
    }

    unique_handle& operator =(std::nullptr_t) noexcept {
      reset();
      return *this;
    }

    explicit operator bool() const noexcept {
      return t_ != null_value;
    }

    void reset(T t) noexcept {
      unique_handle tmp(t);
      swap(tmp);
    }

    T release() noexcept {
      T t(t_);
      t_ = null_value;
      return t;
    }

    void swap(unique_handle& src) noexcept {
      std::swap(t_, src.t_);
    }

    T get() noexcept { return t_; }

  private:
    T t_;
  };

}