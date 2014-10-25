/*
 * ROBIN DEGEN; CONFIDENTIAL
 *
 * 2012 - 2014 Robin Degen
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains the property of
 * Robin Degen and its suppliers, if any. The intellectual and technical
 * concepts contained herein are proprietary to Robin Degen and its suppliers
 * and may be covered by U.S. and Foreign Patents, patents in process, and are
 * protected by trade secret or copyright law. Dissemination of this
 * information or reproduction of this material is strictly forbidden unless
 * prior written permission is obtained from Robin Degen.
 */

#ifndef meshmanager_h__
#define meshmanager_h__

namespace aeon
{

class mesh_manager : public resource_manager,
	public singleton<mesh_manager>
{
public:
	mesh_manager();
	virtual ~mesh_manager();

	mesh_ptr load(stream_ptr stream);
	mesh_ptr load(const std::string &name);

protected:
	resource *__create_new_resource(const std::string &name);
};

} /* namespace aeon */

#endif /* meshmanager_h__ */
