package com.applicaster.cam.config.flow

import com.applicaster.cam.CamFlow
import com.applicaster.cam.ContentAccessManager
import com.applicaster.cam.config.Configurator

class CamFlowResolver {
    companion object {
        /**
         * Updating [CamFlow] based on data from plugin configuration, [AuthenticationRequirement] and check is
         * payment required
         */
        fun updateFlowByConfig(
            originalFlow: CamFlow,
            pluginConfigurator: Configurator
        ): CamFlow {
            val authRequirement: AuthenticationRequirement = pluginConfigurator.getAuthRequirement()
            val paymentRequired: Boolean = pluginConfigurator.isPaymentRequired()
            val isUserLogged: Boolean = ContentAccessManager.contract.isUserLogged()
            val configUpdatedFlow: CamFlow = when (authRequirement) {
                AuthenticationRequirement.NEVER -> {
                    when (originalFlow) {
                        CamFlow.AUTHENTICATION, CamFlow.EMPTY -> CamFlow.EMPTY
                        CamFlow.STOREFRONT, CamFlow.AUTH_AND_STOREFRONT ->
                            if (paymentRequired) CamFlow.STOREFRONT else CamFlow.EMPTY
                    }
                }
                AuthenticationRequirement.ALWAYS -> {
                    when (originalFlow) {
                        CamFlow.AUTHENTICATION, CamFlow.EMPTY -> originalFlow
                        CamFlow.STOREFRONT -> if (paymentRequired) CamFlow.STOREFRONT else CamFlow.EMPTY
                        CamFlow.AUTH_AND_STOREFRONT -> if (paymentRequired) CamFlow.AUTH_AND_STOREFRONT else CamFlow.AUTHENTICATION
                    }
                }
                AuthenticationRequirement.REQUIRE_ON_PURCHASABLE_ITEMS -> {
                    when (originalFlow) {
                        CamFlow.AUTHENTICATION, CamFlow.AUTH_AND_STOREFRONT, CamFlow.EMPTY -> originalFlow
                        CamFlow.STOREFRONT -> if (paymentRequired) CamFlow.AUTH_AND_STOREFRONT else CamFlow.EMPTY
                    }
                }
                AuthenticationRequirement.REQUIRE_WHEN_SPECIFIED_IN_DATA_SOURCE -> {
                    when (originalFlow) {
                        CamFlow.AUTHENTICATION, CamFlow.EMPTY -> originalFlow
                        CamFlow.STOREFRONT, CamFlow.AUTH_AND_STOREFRONT ->
                            if (paymentRequired) originalFlow else CamFlow.EMPTY
                    }
                }
                else -> originalFlow
            }
            return updateFlowByUserState(configUpdatedFlow, paymentRequired, isUserLogged)
        }

        /**
         * Updating [CamFlow] based on user state (logged or not)
         */
        private fun updateFlowByUserState(
            currentFlow: CamFlow,
            paymentRequired: Boolean,
            isUserLogged: Boolean
        ): CamFlow {
            return when (currentFlow) {
                CamFlow.AUTHENTICATION -> if (isUserLogged) CamFlow.EMPTY else currentFlow
                CamFlow.STOREFRONT -> if (paymentRequired) currentFlow else CamFlow.EMPTY
                CamFlow.AUTH_AND_STOREFRONT -> {
                    when (isUserLogged to paymentRequired) {
                        (isUserLogged to paymentRequired) -> CamFlow.STOREFRONT
                        (isUserLogged to !paymentRequired) -> CamFlow.EMPTY
                        (!isUserLogged to paymentRequired) -> CamFlow.AUTH_AND_STOREFRONT
                        (!isUserLogged to !paymentRequired) -> CamFlow.AUTHENTICATION
                        else -> CamFlow.EMPTY
                    }
                }
                CamFlow.EMPTY -> currentFlow
            }
        }
    }
}