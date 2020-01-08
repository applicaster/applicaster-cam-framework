package com.applicaster.cam.ui.billing.adapter.recycler

import android.support.v7.widget.RecyclerView
import android.view.View
import com.applicaster.cam.ui.base.custom.CustomLinkTextView
import kotlinx.android.synthetic.main.layout_bottom_links.view.*

open class CustomLinksViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
    var parentLayout: View = itemView.ll_bottom_links_parent
    var tvLeftLink: CustomLinkTextView = itemView.tv_bottom_link_1
    var tvRightLink: CustomLinkTextView = itemView.tv_bottom_link_2
}