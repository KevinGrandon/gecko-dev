#define MOZ_MUST_USE __attribute__((annotate("moz_must_use")))
#define MOZ_STACK_CLASS __attribute__((annotate("moz_stack_class")))

class MOZ_MUST_USE MOZ_STACK_CLASS TestClass {};

TestClass foo; // expected-error {{variable of type 'TestClass' only valid on the stack}} expected-note {{value incorrectly allocated in a global variable}}

TestClass f()
{
  TestClass bar;
  return bar;
}

void g()
{
  f(); // expected-error {{Unused value of must-use type 'TestClass'}}
}
