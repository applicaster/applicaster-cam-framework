package com.applicaster.cam.ui.billing.adapter.recycler

import android.graphics.Rect
import android.support.v7.widget.RecyclerView
import android.view.View

class SpaceItemDecoration(
    var horizontalSpaceHeight: Int? = null,
    var verticalSpaceHeight: Int? = null
) : RecyclerView.ItemDecoration() {

    override fun getItemOffsets(
        outRect: Rect,
        view: View,
        parent: RecyclerView,
        state: RecyclerView.State
    ) {
        verticalSpaceHeight?.run {
            outRect.top = this / 2
            outRect.bottom = this / 2
        }
        horizontalSpaceHeight?.run {
            outRect.left = this / 2
            outRect.right = this / 2
        }
    }
}