package com.applicaster.cam.ui.billing.adapter.pager

import android.support.v4.view.ViewPager
import android.content.Context
import android.graphics.Point
import android.view.MotionEvent
import android.util.AttributeSet
import android.view.View
import android.widget.FrameLayout


class PagerContainer : FrameLayout, ViewPager.OnPageChangeListener {

    var viewPager: ViewPager? = null
        private set

    var needsRedraw = false

    private val center = Point()
    private val initialTouch = Point()

    constructor(context: Context) : super(context) {
        init()
    }

    constructor(context: Context, attrs: AttributeSet) : super(context, attrs) {
        init()
    }

    constructor(context: Context, attrs: AttributeSet, defStyle: Int) : super(context, attrs, defStyle) {
        init()
    }

    private fun init() {
        //Disable clipping of children so non-selected pages are visible
        clipChildren = false

        //Child clipping doesn't work with hardware acceleration in Android 3.x/4.x
        //You need to set this value here if using hardware acceleration in an
        // application targeted at these releases.
        setLayerType(View.LAYER_TYPE_SOFTWARE, null)
    }

    override fun onFinishInflate() {
        super.onFinishInflate()
        try {
            viewPager = getChildAt(0) as ViewPager
            viewPager?.addOnPageChangeListener(this)
        } catch (e: Exception) {
            throw IllegalStateException("The root child of PagerContainer must be a ViewPager")
        }

    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        center.x = w / 2
        center.y = h / 2
    }

    override fun onTouchEvent(ev: MotionEvent): Boolean {
        //We capture any touches not already handled by the ViewPager
        // to implement scrolling from a touch outside the pager bounds.
        when (ev.action) {
            MotionEvent.ACTION_DOWN -> {
                initialTouch.x = ev.x.toInt()
                initialTouch.y = ev.y.toInt()
                ev.offsetLocation((center.x - initialTouch.x).toFloat(), (center.y - initialTouch.y).toFloat())
            }
            else -> ev.offsetLocation((center.x - initialTouch.x).toFloat(), (center.y - initialTouch.y).toFloat())
        }

        return viewPager?.dispatchTouchEvent(ev) ?: false
    }

    override fun onPageScrolled(position: Int, positionOffset: Float, positionOffsetPixels: Int) {
        //Force the container to redraw on scrolling.
        //Without this the outer pages render initially and then stay static
        if (needsRedraw) invalidate()
    }

    override fun onPageSelected(position: Int) {}

    override fun onPageScrollStateChanged(state: Int) {
        needsRedraw = state != ViewPager.SCROLL_STATE_IDLE
    }
}