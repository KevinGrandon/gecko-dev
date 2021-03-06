/* -*- Mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; tab-width: 40 -*- */
/* vim: set ts=2 et sw=2 tw=80: */
/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef mozilla_dom_PresentationChild_h
#define mozilla_dom_PresentationChild_h

#include "mozilla/dom/PPresentationChild.h"
#include "mozilla/dom/PPresentationRequestChild.h"

class nsIPresentationServiceCallback;

namespace mozilla {
namespace dom {

class PresentationIPCService;

class PresentationChild final : public PPresentationChild
{
public:
  explicit PresentationChild(PresentationIPCService* aService);

  virtual void
  ActorDestroy(ActorDestroyReason aWhy) override;

  virtual PPresentationRequestChild*
  AllocPPresentationRequestChild(const PresentationIPCRequest& aRequest) override;

  virtual bool
  DeallocPPresentationRequestChild(PPresentationRequestChild* aActor) override;

  virtual bool
  RecvNotifyAvailableChange(const bool& aAvailable) override;

  virtual bool
  RecvNotifySessionStateChange(const nsString& aSessionId,
                               const uint16_t& aState) override;

  virtual bool
  RecvNotifyMessage(const nsString& aSessionId,
                    const nsCString& aData) override;

  virtual bool
  RecvNotifySessionConnect(const uint64_t& aWindowId,
                           const nsString& aSessionId) override;

private:
  virtual ~PresentationChild();

  bool mActorDestroyed;
  nsRefPtr<PresentationIPCService> mService;
};

class PresentationRequestChild final : public PPresentationRequestChild
{
  friend class PresentationChild;

public:
  explicit PresentationRequestChild(nsIPresentationServiceCallback* aCallback);

  virtual void
  ActorDestroy(ActorDestroyReason aWhy) override;

  virtual bool
  Recv__delete__(const nsresult& aResult) override;

private:
  virtual ~PresentationRequestChild();

  bool mActorDestroyed;
  nsCOMPtr<nsIPresentationServiceCallback> mCallback;
};

} // namespace dom
} // namespace mozilla

#endif // mozilla_dom_PresentationChild_h
