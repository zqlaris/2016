package com.arkiv.hybrid.modules;

import com.arkiv.hybrid.RBHybridCommand;
import com.arkiv.hybrid.RBHybridModule;

/**
 * Created by arkiv on 3/6/15.
 */
public class RBHybridModuleAnalytics extends RBHybridModule {
    private static final String MODULE_ID = "Analytics";

    public RBHybridModuleAnalytics() {
        super(MODULE_ID);
    }

    @Override
    public void execute(RBHybridCommand command) {
        command.executeCallback(true, null);
    }
}
