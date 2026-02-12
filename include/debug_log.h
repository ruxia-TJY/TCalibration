//
// Created by jared on 2026/2/6.
//

#ifndef BD_DEBUG_LOG_H
#define BD_DEBUG_LOG_H

#define DEBUG_LOG() \
qDebug() << "File:" << __FILE__ << ", Line:" << __LINE__ << ",Function:" << Q_FUNC_INFO

#define NOFILE_DEBUG_LOG() \
qDebug() << "Line:" << __LINE__ << ",Function:" << Q_FUNC_INFO


#endif //BD_DEBUG_LOG_H